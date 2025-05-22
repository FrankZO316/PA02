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
struct Movie {
    string name;
    double rating;
    Movie(string n, double r) : name(n), rating(r) {}
};
int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> movies;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            movies.emplace_back(movieName, movieRating);// Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    }

    movieFile.close();
    sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.name < b.name;
    });
    if (argc == 2){
            for (const Movie& m : movies) {
            cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
        }//print all the movies in ascending alphabetical order of movie names
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
     vector<Movie> bestMovies;
    vector<bool> hasMovies;

    for (const string& prefix : prefixes) {
        auto lower = lower_bound(movies.begin(), movies.end(), prefix, [&](const Movie& m, const string& p) {
            return m.name.substr(0, p.length()) < p;
        });
        auto upper = upper_bound(movies.begin(), movies.end(), prefix, [&](const string& p, const Movie& m) {
            return p < m.name.substr(0, p.length());
        });

        vector<Movie> matches(lower, upper);
        if (matches.empty()) {
            cout << "No movies found with prefix " << prefix << endl;
            bestMovies.emplace_back("", -1.0);
            hasMovies.push_back(false);
        } else {
            sort(matches.begin(), matches.end(), [](const Movie& a, const Movie& b) {
                if (a.rating != b.rating) return a.rating > b.rating;
                return a.name < b.name;
            });
            for (const Movie& m : matches) {
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
            }
            cout << endl;
            bestMovies.push_back(matches.front());
            hasMovies.push_back(true);
        }
    }

    for (size_t i = 0; i < prefixes.size(); ++i) {
        if (hasMovies[i]) {
            cout << "Best movie with prefix " << prefixes[i] << " is: " << bestMovies[i].name
                 << " with rating " << fixed << setprecision(1) << bestMovies[i].rating << endl;
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
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}