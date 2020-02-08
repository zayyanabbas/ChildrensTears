#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

namespace ChildrensTears {
    // Returns a map with the key being the first word of the line
    // and associated value being second word
    std::unordered_map<std::string, std::string> readConfigFile(std::string path);

    // Splits a string into a vector based on a separating character
    std::vector<std::string> split_string(std::string original, char separator);
}