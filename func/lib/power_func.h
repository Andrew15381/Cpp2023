//
// Created by andrew on 27.11.23.
//

#ifndef MATKIB_POWER_FUNC_H
#define MATKIB_POWER_FUNC_H

#include <sstream>
#include <cmath>
#include "func.h"

namespace FuncLib {
    /*!
     * Класс для степенной функции
     */
    class PowerFunc : public Func {
        double _power;
        std::string _s;
    public:
        /*!
         * Класс для создания степенной функции
         */
        class PowerFuncCreator : public FuncCreator {
        public:
            /*!
             * Создает степенную функцию
             * @param args степень
             * @return степенная функция
             */
            FuncPtr create(std::any &&args) override {
                return std::make_shared<PowerFunc>(std::any_cast<double>(args));
            }
        };
        /*!
         * Создает степенную функцию
         * @param power степень
         */
        PowerFunc(double power) : _power(power) {
            std::stringstream ss;
            if (power >= 0) {
                ss << "x^" << power;
            } else if (power < 0) {
                ss << "x^(" << power << ")";
            }
            _s = ss.str();
        }
        /*!
         * Вычисляет значение степенной функции в точке x
         * @param x точка
         * @return значение функции
         */
        double operator()(double x) const override {
            return std::pow(x, _power);
        }
        /*!
         * Вычисляет значение производной степенной функции в точке x
         * @param x точка
         * @return значение произвоодной
         */
        double derive(double x) const override {
            return _power * std::pow(x, _power - 1);
        }
        /*!
         * Переводит объект в строковое представление, отрицательная степень берется в скобки.
         * @return "x^степень"
         */
        std::string to_string() const override {
            return _s;
        }
    };
}

#endif //MATKIB_POWER_FUNC_H
