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
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename [prefixFilename]" << endl;
        exit(1);
    }

    ifstream movieFile(argv[1]);
    if (movieFile.fail()) {
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    vector<Movie> movies;
    string line, movieName;
    double movieRating;

    while (getline(movieFile, line) && parseLine(line, movieName, movieRating)) {
        movies.emplace_back(movieName, movieRating);
    }

    movieFile.close();
    sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.name < b.name;
    });

    if (argc == 2) {
        for (const Movie& m : movies) {
            cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
        }
        return 0;
    }

    ifstream prefixFile(argv[2]);
    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    vector<Movie> bestMovies;
    vector<bool> hasMatches;

    while (getline(prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    // First pass: Process matches and collect best movies
   for (const string& prefix : prefixes) {
    vector<Movie> matches;

    if (matches.empty()) {
        cout << "No movies found with prefix " << prefix << endl;
    } else {
        // Print matches
        for (const Movie& m : matches) {
            cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
        }
        // Find and print best movie
        auto best_it = max_element(matches.begin(), matches.end(), 
            [](const Movie& a, const Movie& b) {
                return (a.rating < b.rating) || (a.rating == b.rating && a.name > b.name);
            });
        cout << "Best movie with prefix " << prefix << " is: " 
             << best_it->name << " with rating " << best_it->rating << endl;
    }
    
    cout << endl;  
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