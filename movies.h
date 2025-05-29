#ifndef MOVIES_H
#define MOVIES_H

#include <vector>
#include <string>
#include <map>
#include <utility>

class MovieDatabase {
public:
    void insertMovie(const std::string& name, double rating);
    void printAllAlphabetically() const;
    void processPrefixQueries(const std::vector<std::string>& prefixes) const;

private:
    std::vector<std::pair<std::string, double>> movies;
    mutable std::map<std::string, std::vector<std::pair<double, std::string>>> prefixMap;
    mutable std::map<std::string, std::pair<std::string, double>> bestMovieCache;
    
    void buildPrefixIndex() const;
    bool printMoviesForPrefix(const std::string& prefix) const;  // Changed to bool
    void printBestMovieForPrefix(const std::string& prefix) const;
};

#endif