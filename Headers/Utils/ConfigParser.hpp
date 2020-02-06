#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

// Returns a map with the key being the first word of the line
// and associated value being second word
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
        std::string args = line.substr(line.find(' '), line.size());

        // Insert this into map
        ret.insert({key,args});
    }

    return ret;
}

std::vector<std::string> split_string(std::string original, char separator) {
    std::vector<std::string> results;
    std::string::const_iterator start = original.begin();
    std::string::const_iterator end = original.end();
    std::string::const_iterator next = std::find(start, end, separator);
    while ( next != end ) {
        results.push_back(std::string(start, next));
        start = next + 1;
        next = std::find(start, end, separator);
    }
    results.push_back( std::string(start, next));
    return results;
}