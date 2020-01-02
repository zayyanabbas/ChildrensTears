#pragma once    
#include <bits/stdc++.h>
#include <type_traits>

namespace ChildrensTears {
    namespace Constants {
        constexpr uint32_t MaxEntities = 2;
        constexpr uint8_t MaxComponents = 3;
        constexpr double pi = 3.1415;
    }

    typedef uint32_t EntityID;
    typedef std::bitset<Constants::MaxComponents> Signature;
}