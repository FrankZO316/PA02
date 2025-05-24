#include "movies.h"
#include <algorithm>

void Movies::addMovie(const std::string& name, double rating) {
    movies.push_back({name, rating});
}

void Movies::sortMovies() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.name < b.name;
    });
}

std::vector<Movie> Movies::getMoviesByPrefix(const std::string& prefix) const {
    std::vector<Movie> result;
 
    auto lower = std::lower_bound(movies.begin(), movies.end(), prefix,
        [](const Movie& m, const std::string& p) {
            return m.name.compare(0, p.size(), p) < 0;
        });
    auto upper = std::upper_bound(movies.begin(), movies.end(), prefix,
        [](const std::string& p, const Movie& m) {
            return p.compare(0, p.size(), m.name.substr(0, p.size())) < 0;
        });
    result.assign(lower, upper);
    return result;
}

Movie Movies::findBestMovie(const std::string& prefix) const {
    auto matches = getMoviesByPrefix(prefix);
    if (matches.empty()) return {"", -1.0};
    
    return *std::max_element(matches.begin(), matches.end(),
        [](const Movie& a, const Movie& b) {
            return (a.rating < b.rating) || 
                   (a.rating == b.rating && a.name > b.name);
        });
}

const std::vector<Movie>& Movies::getMoviesList() const {
    return movies;
}