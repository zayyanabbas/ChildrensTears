#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

std::unordered_map<std::string, std::string> readConfigFile(std::string path) {
    std::string line;
    std::ifstream in(path);

    std::unordered_map<std::string,std::string> ret;

    assert(in.is_open() && "Config file path incorrect");

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::vector<std::string> inVec(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());

        ret.insert({inVec[0],inVec[1]});
    }

    return ret;
}