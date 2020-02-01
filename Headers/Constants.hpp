#pragma once    
#include <bits/stdc++.h>
#include <type_traits>
#include "Utils/ConfigParser.hpp"

namespace ChildrensTears {
    namespace Constants {
        uint32_t MaxEntities = std::stoi(readConfigFile("./config.cfg").find("MaxEntities")->second);
        constexpr uint8_t MaxComponents = 4;
    }

    typedef uint32_t EntityID;
    typedef std::bitset<Constants::MaxComponents> Signature;
}