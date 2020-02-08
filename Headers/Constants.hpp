#pragma once    
#include <bits/stdc++.h>
#include <type_traits>
#include "Utils/ConfigParser.hpp"

namespace ChildrensTears {
    // Constants needed for the engine to work
    namespace Constants {
        // Maximum number of entities allowed by the engine
        // Read from a config file
        static uint32_t MaxEntities = std::stoi(readConfigFile("./config.cfg").find("MaxEntities")->second);

        // Total number of components
        // Can't be changed out of code
        static constexpr uint8_t MaxComponents = 4;
    }

    // Convenient aliases
    typedef uint32_t EntityID;
    typedef std::bitset<Constants::MaxComponents> Signature;
}