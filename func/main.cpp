//
// Created by andrew on 27.11.23.
//

#include <iostream>
#include <vector>
#include "lib/func.h"

int main() {
    std::vector<FuncPtr> cont;
    auto f = Func::_factory.create("power", 2.0); // PowerFunc x^2
    cont.push_back(f);
    auto g = Func::_factory.create("polynomial", std::vector<double>{7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3
    cont.push_back(g);
    for (const auto ptr : cont) {
        std::cout << ptr->to_string() << " for x = 10 is " << (*ptr)(10) << std::endl;
    }
    auto p = *f + *g;
    p.derive(1); // 15
    auto h = *f + "abc"; // std::logic_error
    f->derive(3); // 6
    return 0;
}