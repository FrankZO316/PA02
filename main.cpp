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

// ... (previous includes and declarations remain the same)

int main(int argc, char** argv) {
    // ... (initial setup remains the same)

    ifstream prefixFile(argv[2]);
    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    string line;
    while (getline(prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    for (const string& prefix : prefixes) {
        vector<Movie> matches;
        auto lower = lower_bound(movies.begin(), movies.end(), prefix,
            [](const Movie& m, const string& p) {
                return m.name.compare(0, p.length(), p) < 0;
            });
        auto upper = upper_bound(movies.begin(), movies.end(), prefix,
            [](const string& p, const Movie& m) {
                return p.compare(0, p.length(), m.name.substr(0, p.length())) < 0;
            });

        matches.assign(lower, upper);

        if (matches.empty()) {
            cout << "No movies found with prefix " << prefix << endl; // Fixed newline
        } else {
            // Find best movie efficiently
            auto best_it = max_element(matches.begin(), matches.end(),
                [](const Movie& a, const Movie& b) {
                    return (a.rating < b.rating) || 
                           (a.rating == b.rating && a.name > b.name);
                });
            Movie best = *best_it;

            // Print matches sorted lexicographically (as they're from sorted movies)
            // Since movies are already sorted, matches are in lex order
            for (const Movie& m : matches) {
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
            }

            // Print best movie immediately after matches
            cout << "Best movie with prefix " << prefix << " is: " 
                 << best.name << " with rating " 
                 << fixed << setprecision(1) << best.rating << endl;
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