#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>

struct Movie {
    std::string name;
    double rating;
};

class Movies {
public:
    void addMovie(const std::string& name, double rating);
    void sortMovies();
    std::vector<Movie> getMoviesByPrefix(const std::string& prefix) const;
    Movie findBestMovie(const std::string& prefix) const;
    const std::vector<Movie>& getMoviesList() const;

private:
    std::vector<Movie> movies;
};

#endif 