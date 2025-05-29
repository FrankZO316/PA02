#include "utilities.h"
#include <string>

using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating) {
    if (line.empty()) return false;
    
    int commaIndex = line.find_last_of(",");
    if (commaIndex == string::npos) return false;
    
    movieName = line.substr(0, commaIndex);
    try {
        movieRating = stod(line.substr(commaIndex+1));
    } catch (...) {
        return false;
    }
    
    // Remove quotes if present
    if (movieName.front() == '"' && movieName.back() == '"') {
        movieName = movieName.substr(1, movieName.length()-2);
    }
    
    return true;
}
