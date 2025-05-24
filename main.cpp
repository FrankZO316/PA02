// Winter'24
// Instructor: Diba Mirza
// Student name: Zhentao Ouyang
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv) {
    std::vector<Movie> movies;
    std::string line, movieName;
    double movieRating;

    // Read movie data from standard input until an empty line is encountered
    while (std::getline(std::cin, line)) {
        if (line.empty()) break; // Empty line indicates end of movie data
        if (parseLine(line, movieName, movieRating)) {
            movies.emplace_back(movieName, movieRating);
        }
    }

    // Sort movies alphabetically by name
    std::sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b) {
        return a.name < b.name;
    });

    // Output the sorted list of movies
    for (const Movie &m : movies) {
        std::cout << m.name << ", " << std::fixed << std::setprecision(1) << m.rating << std::endl;
    }

    // Read prefixes from standard input
    std::vector<std::string> prefixes;
    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    // Process each prefix
    for (const std::string &prefix : prefixes) {
        std::vector<Movie> matches;
        auto lower = std::lower_bound(movies.begin(), movies.end(), prefix,
            [](const Movie &m, const std::string &p) {
                return m.name.compare(0, p.length(), p) < 0;
            });
        auto upper = std::upper_bound(movies.begin(), movies.end(), prefix,
            [](const std::string &p, const Movie &m) {
                return p.compare(0, p.length(), m.name.substr(0, p.length())) < 0;
            });

        matches.assign(lower, upper);

        if (matches.empty()) {
            std::cout << "No movies found with prefix " << prefix << std::endl;
        } else {
            for (const Movie &m : matches) {
                std::cout << m.name << ", " << std::fixed << std::setprecision(1) << m.rating << std::endl;
            }

            Movie best = matches[0];
            for (const Movie &m : matches) {
                if (m.rating > best.rating ||
                    (m.rating == best.rating && m.name < best.name)) {
                    best = m;
                }
            }

            std::cout << "Best movie with prefix " << prefix << " is "
                      << best.name << " with rating " << best.rating << std::endl;
            std::cout << std::endl;
        }
    }

    

    return 0;
}
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.


/* Time Complexity Analysis (Part 3a):
- Reading and sorting n movies: O(n log n)
- For each of m prefixes:
- Binary search to find prefix range: O(log n)
- Sorting k movies by rating and name: O(k log k)
- Total time complexity: O(n log n + m (log n + k log k))

Space Complexity Analysis (Part 3b):
- Storing n movies: O(n)
- Temporary storage for k movies per prefix: O(k)
- Total space complexity: O(n + k)

Trade-offs (Part 3c):
Optimized for time efficiency using binary search for quick 
prefix lookups. Sorting the prefix subset ensures correct order 
for output and highest-rated movie selection. Space usage is kept 
linear with input size, acceptable for large datasets.*/

bool parseLine(string &line, string &movieName, double &movieRating) {
         size_t comma = line.find_last_of(',');
    if (comma == string::npos) return false;
    movieName = line.substr(0, comma);
    try {
        movieRating = stod(line.substr(comma + 1));
    } catch (...) {
        return false;
    }
    if (!movieName.empty() && movieName.front() == '\"') {
        movieName = movieName.substr(1, movieName.size() - 2);
    }
    return true;
}