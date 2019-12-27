#pragma once    
#include <bits/stdc++.h>

namespace ChildrensTears {
    typedef uint32_t EntityID;

    namespace Constants {
        constexpr uint32_t MaxEntities = 2;
        constexpr uint8_t MaxComponents = 3;
    }

    typedef std::bitset<Constants::MaxComponents> Signature;
}