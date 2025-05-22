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
            return m.name.compare(0, p.size(), p) > 0;
        });
    result.assign(lower, upper);
    std::sort(result.begin(), result.end(), [](const Movie& a, const Movie& b) {
        if (a.rating != b.rating) return a.rating > b.rating;
        return a.name < b.name;
    });
    return result;
}

Movie Movies::findBestMovie(const std::string& prefix) const {
    auto matches = getMoviesByPrefix(prefix);
    return matches.empty() ? Movie{"", -1.0} : matches.front();
}

const std::vector<Movie>& Movies::getMoviesList() const {
    return movies;
}