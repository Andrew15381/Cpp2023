//
// Created by andrew on 27.11.23.
//

#ifndef MATKIB_POLYNOMIAL_FUNC_H
#define MATKIB_POLYNOMIAL_FUNC_H

#include <sstream>
#include <vector>
#include "func.h"

namespace FuncLib {
    /*!
     * Класс для полиномиальной функции
     */
    class PolynomialFunc : public Func {
        std::vector<double> _coeffs;
        std::string _s;
    public:
        /*!
         * Класс для создания полиномиальной функции
         */
        class PolynomialFuncCreator : public FuncCreator {
        public:
            /*!
             * Создает полиномиальную функцию
             * @param args коэффициенты с 0 степени
             * @return полиномиальная функция
             */
            FuncPtr create(std::any &&args) override {
                return std::make_shared<PolynomialFunc>(
                        std::forward<std::vector<double>>(std::any_cast<std::vector<double>>(args)));
            }
        };
        /*!
         * Сощдает полиномиальную функцию
         * @param coeffs коэффициенты с 0 степени
         */
        PolynomialFunc(std::vector<double>&& coeffs) : _coeffs(coeffs) {
            if (coeffs.size() > 0) {
                std::stringstream ss;
                ss << coeffs[0];
                for (size_t i = 1; i < coeffs.size(); ++i) {
                    if (coeffs[i] > 0) {
                        ss << " + " << coeffs[i] << "*x^" << i;
                    } else if (coeffs[i] < 0) {
                        ss << " + (" << coeffs[i] << ")*x^" << i;
                    }
                }
                _s = ss.str();
            } else {
                _s = "0";
            }
        }
        /*!
         * Вычисляет значение полиномиальной функции в точке x
         * @param x точка
         * @return значение функции
         */
        double operator()(double x) const override {
            double sum = 0, power = 1;
            for (size_t i = 0; i < _coeffs.size(); ++i) {
                sum += _coeffs[i] * power;
                power *= x;
            }
            return sum;
        }
        /*!
         * Вычисляет значение производной полиномиальной функции в точке x
         * @param x точка
         * @return значение производной
         */
        double derive(double x) const override {
            double sum = 0, power = 1;
            for (size_t i = 1; i < _coeffs.size(); ++i) {
                sum += _coeffs[i] * power * i;
                power *= x;
            }
            return sum;
        }
        /*!
         * Переводит объект в строковое представление, отрицательные коэффициенты берутся в скобки
         * @return "c0 + c1*x^1 + c2*x^2 + ..."
         */
        std::string to_string() const override {
            return _s;
        }
    };
}

#endif //MATKIB_POLYNOMIAL_FUNC_H
