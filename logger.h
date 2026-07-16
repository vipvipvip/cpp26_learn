#pragma once

#include "types.h"
#include <source_location>
#include <stacktrace>

void log_result(const Command& cmd, const CalcResult& result,
                std::source_location loc = std::source_location::current());
void log_stacktrace(std::string_view label);
