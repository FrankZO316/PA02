#include "utilities.h"
#include <string>

bool parseLine(std::string &line, std::string &movieName, double &movieRating) {
    size_t comma = line.find_last_of(',');
    if (comma == std::string::npos) return false;
    movieName = line.substr(0, comma);
    try {
        movieRating = std::stod(line.substr(comma + 1));
    } catch (...) {
        return false;
    }
    if (!movieName.empty() && movieName.front() == '\"') {
        movieName = movieName.substr(1, movieName.size() - 2);
    }
    return true;
}