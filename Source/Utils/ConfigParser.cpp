#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include "../../Headers/Utils/ConfigParser.hpp"

namespace ChildrensTears {
    std::unordered_map<std::string, std::string> readConfigFile(std::string path) {
        std::string line;
        std::ifstream in(path);

        std::unordered_map<std::string,std::string> ret;

        // Check if config file exists
        assert(in.is_open() && "Can't find config file");

        // Go through whole file
        while (std::getline(in, line)) {
            // Separate the key and arguments
            std::string key = line.substr(0, line.find(' '));
            std::string args = line.substr(line.find(' ') + 1, line.size());

            // Insert this into map
            ret.insert({key,args});
        }

        return ret;
    }

    std::vector<std::string> linesFromFile(std::string path) {
        std::string line;
        std::ifstream in(path);
        std::vector<std::string> ret;
        assert(in.is_open() && "Can't find file");
        while (std::getline(in, line)) {
            ret.push_back(line);
        }
        return ret;
    }

    std::vector<std::string> split_string(std::string original, char separator) {
        std::vector<std::string> results;
   
        std::string::const_iterator start = original.begin();
        std::string::const_iterator end = original.end();
        std::string::const_iterator next = std::find(start, end, separator);
   
       // While not all of the characters have been found
        while ( next != end ) {
            // Push back substring from the last separator to next
            results.push_back(std::string(start, next));

            // Go to the start of the next word
            start = next + 1;

            // Find the next separator
            next = std::find(start, end, separator);
        }

        // Push back final word
        results.push_back( std::string(start, next));
    
        return results;
    }
}