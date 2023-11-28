//
// Created by andrew on 28.11.23.
//

#include "lib/func.h"
#include <gtest/gtest.h>

using namespace FuncLib;

TEST(Stage1, Create) {
    auto constant = Func::_factory.create("const", 10.0);
    auto ident = Func::_factory.create("ident");
    auto power = Func::_factory.create("power", 2.0);
    auto poly = Func::_factory.create("polynomial", std::vector<double>{1, 2, 3});
    auto exp = Func::_factory.create("exp", 2.718281828);
    EXPECT_NE(std::static_pointer_cast<ConstFunc>(constant), nullptr);
    EXPECT_NE(std::static_pointer_cast<IdentFunc>(ident), nullptr);
    EXPECT_NE(std::static_pointer_cast<PowerFunc>(power), nullptr);
    EXPECT_NE(std::static_pointer_cast<PolynomialFunc>(poly), nullptr);
    EXPECT_NE(std::static_pointer_cast<ExpFunc>(exp), nullptr);
}

TEST(Stage1, Value) {
    auto constant = Func::_factory.create("const", 10.0);
    auto ident = Func::_factory.create("ident");
    auto power = Func::_factory.create("power", 2.0);
    auto poly = Func::_factory.create("polynomial", std::vector<double>{1, 2, 3});
    auto exp = Func::_factory.create("exp", 2.0);
    EXPECT_EQ((*constant)(0), 10);
    EXPECT_EQ((*constant)(10), 10);
    EXPECT_EQ((*ident)(0), 0);
    EXPECT_EQ((*constant)(10), 10);
    EXPECT_EQ((*power)(0), 0);
    EXPECT_EQ((*power)(10), 100);
    EXPECT_EQ((*poly)(0), 1);
    EXPECT_EQ((*poly)(10), 321);
    EXPECT_EQ((*exp)(0), 1);
    EXPECT_EQ((*exp)(10), 1024);
}

TEST(Stage1, Str) {
    auto constant = Func::_factory.create("const", 123.123);
    auto ident = Func::_factory.create("ident");
    auto power = Func::_factory.create("power", -2.5);
    auto poly = Func::_factory.create("polynomial", std::vector<double>{1.1, 2.2, -3.3, 0});
    auto exp = Func::_factory.create("exp", 2.0);
    EXPECT_STREQ(constant->to_string().c_str(), "123.123");
    EXPECT_STREQ(ident->to_string().c_str(), "x");
    EXPECT_STREQ(power->to_string().c_str(), "x^(-2.5)");
    EXPECT_STREQ(poly->to_string().c_str(), "1.1 + 2.2*x^1 + (-3.3)*x^2");
    EXPECT_STREQ(exp->to_string().c_str(), "2^x");
}

TEST(Stage2, Ops) {
    double x = 10.0;
    std::vector<FuncPtr> funcs = {Func::_factory.create("const", 10.0),
                                  Func::_factory.create("ident"),
                                  Func::_factory.create("power", 2.0),
                                  Func::_factory.create("polynomial", std::vector<double>{1, 2, 3}),
                                  Func::_factory.create("exp", 2.718281828)};
    for (int i = 0; i < funcs.size(); ++i) {
        EXPECT_THROW(*funcs[i] + 123, std::logic_error);
        for (int j = 0; j < funcs.size(); ++j) {
            for (int k = 0; k < funcs.size(); ++k) {
                EXPECT_EQ((*funcs[i] + *funcs[j])(x), (*funcs[i])(x) + (*funcs[j])(x));
                EXPECT_EQ((*funcs[i] - *funcs[j])(x), (*funcs[i])(x) - (*funcs[j])(x));
                EXPECT_EQ((*funcs[i] / *funcs[j])(x), (*funcs[i])(x) / (*funcs[j])(x));
                EXPECT_EQ((*funcs[i] * *funcs[j])(x), (*funcs[i])(x) * (*funcs[j])(x));
            }
        }
    }
}

TEST(Stage3, Derivative) {
    double x = 10;
    auto constant = Func::_factory.create("const", 10.0);
    auto ident = Func::_factory.create("ident");
    auto power = Func::_factory.create("power", 3.0);
    auto poly = Func::_factory.create("polynomial", std::vector<double>{0, 10, 1, 10});
    auto exp = Func::_factory.create("exp", 2.0);
    EXPECT_EQ((*constant * *ident + (*ident) * (*ident) + (*constant) * (*power)).derive(x), poly->derive(x));
    EXPECT_EQ(exp->derive(0), std::log(2.0));
}

TEST(Stage4, Solution) {
    auto constant = Func::_factory.create("const", 10.0);
    auto ident = Func::_factory.create("ident");
    auto poly = Func::_factory.create("polynomial", std::vector<double>{1, -2, 1, });
    EXPECT_EQ(solve(*ident - *constant, 0.0, 1.0, 10), -10.0);
    EXPECT_LT(std::abs(solve(*poly, 0.5, 1e-2, 1000) - 1), 1e-3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}