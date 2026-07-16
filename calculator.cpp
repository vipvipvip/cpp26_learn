#include "calculator.h"

#include <cmath>

CalcResult compute(const Command& cmd) {
    switch (cmd.op) {
        case Op::Add:
            return cmd.lhs + cmd.rhs;
        case Op::Sub:
            return cmd.lhs - cmd.rhs;
        case Op::Mul:
            return cmd.lhs * cmd.rhs;
        case Op::Div:
            if (std::abs(cmd.rhs) < 1e-12)
                return std::unexpected("division by zero");
            return cmd.lhs / cmd.rhs;
    }
    return std::unexpected("unknown operator");
}

std::string_view op_name(Op op) {
    switch (op) {
        case Op::Add: return "+";
        case Op::Sub: return "-";
        case Op::Mul: return "*";
        case Op::Div: return "/";
    }
    return "?";
}
