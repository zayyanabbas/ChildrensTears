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
        // Separate files into a vector wtih words
        std::istringstream iss(line);
        std::vector<std::string> inVec(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());

        // Insert this into map
        ret.insert({inVec[0],inVec[1]});
    }

    return ret;
}