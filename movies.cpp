#include "movies.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

void MovieDatabase::insertMovie(const string& name, double rating) {
    movies.emplace_back(name, rating);
}

void MovieDatabase::printAllAlphabetically() const {
    vector<pair<string, double>> sortedMovies = movies;
    sort(sortedMovies.begin(), sortedMovies.end());
    
    for (const auto& movie : sortedMovies) {
        cout << movie.first << ", " << fixed << setprecision(1) << movie.second << endl;
    }
}

void MovieDatabase::buildPrefixIndex() const {
    for (const auto& movie : movies) {
        const string& name = movie.first;
        double rating = movie.second;
        
        for (size_t len = 1; len <= name.size(); len++) {
            string prefix = name.substr(0, len);
            prefixMap[prefix].emplace_back(rating, name);
        }
    }
    
    for (auto& entry : prefixMap) {
        auto& movieList = entry.second;
        sort(movieList.begin(), movieList.end(), 
            [](const auto& a, const auto& b) {
                return a.first > b.first || (a.first == b.first && a.second < b.second);
            });
        
        if (!movieList.empty()) {
            bestMovieCache[entry.first] = {movieList[0].second, movieList[0].first};
        }
    }
}

void MovieDatabase::printMoviesForPrefix(const string& prefix) const {
    auto it = prefixMap.find(prefix);
    if (it == prefixMap.end() || it->second.empty()) {
        cout << "No movies found with prefix " << prefix << endl;
        return;
    }
    
    for (const auto& movie : it->second) {
        cout << movie.second << ", " << fixed << setprecision(1) << movie.first << endl;
    }
}

void MovieDatabase::processPrefixQueries(const vector<string>& prefixes) const {
    if (prefixMap.empty()) {
        buildPrefixIndex();
    }
    
    for (const auto& prefix : prefixes) {
        printMoviesForPrefix(prefix);
    }
    
    cout << endl; 
    for (const auto& prefix : prefixes) {
        auto it = bestMovieCache.find(prefix);
        if (it != bestMovieCache.end()) {
            cout << "Best movie with prefix " << prefix << " is: " 
                 << it->second.first << " with rating " << fixed << setprecision(1) 
                 << it->second.second << endl;
        }
    }
}