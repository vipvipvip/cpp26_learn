#include "reflection/reflect.h"
#include "models/stock_ticker.h"

#include <print>
#include <typeinfo>

namespace {

// Simulates what C++26 reflection will provide automatically.
// When P2996 lands, this becomes:
//   for (constexpr auto m : std::meta::members_of(^StockTicker))
//       fields.push_back({std::meta::display_name_of(m),
//                         std::meta::type_of(m) | std::meta::display_name_of});

std::vector<ReflectedField> reflect_stock_ticker() {
    // Manual "reflection" — replaced by compiler-generated code in C++26
    return {
        {"id",          typeid(decltype(StockTicker::id)).name()},
        {"symbol",      typeid(decltype(StockTicker::symbol)).name()},
        {"enabled",     typeid(decltype(StockTicker::enabled)).name()},
        {"company_name", typeid(decltype(StockTicker::company_name)).name()},
        {"is_etf",      typeid(decltype(StockTicker::is_etf)).name()},
        {"created_at",  typeid(decltype(StockTicker::created_at)).name()},
        {"updated_at",  typeid(decltype(StockTicker::updated_at)).name()},
    };
}

}  // namespace

void run_reflection_demo() {
    std::println("=== Reflection Demo (P2996 placeholder) ===\n");
    std::println("C++26 reflection not yet in GCC 15. Using manual introspection:\n");

    auto fields = reflect_stock_ticker();

    std::println("StockTicker fields ({}):", fields.size());
    for (const auto& f : fields) {
        std::println("  {:<15} -> {}", f.name, f.type_name);
    }

    std::println("\n// With C++26 reflection, this becomes:\n"
                 "//   for (constexpr auto m : std::meta::members_of(^StockTicker))\n"
                 "//       print_field(m);");
}
