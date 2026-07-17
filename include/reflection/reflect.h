#pragma once

// C++26 static reflection is not yet available in GCC 15.
// Track: https://wg21.link/P2996
//
// When available, you will be able to do:
//   for (constexpr auto member : std::meta::members_of(^StockTicker))
//       std::println("{}: {}", std::meta::display_name_of(member),
//                     std::meta::type_of(member));
//
// For now, this module demonstrates what reflection will enable
// using manual type introspection as a placeholder.

#include <string>
#include <vector>

struct ReflectedField {
    std::string name;
    std::string type_name;
};

void run_reflection_demo();
