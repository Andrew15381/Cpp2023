//
// Created by andrew on 27.11.23.
//

#ifndef MATKIB_EXP_FUNC_H
#define MATKIB_EXP_FUNC_H

#include <sstream>
#include <cmath>
#include <stdexcept>
#include "func.h"

namespace FuncLib {
    /*!
     * Класс для экспоненциальной функции
     */
    class ExpFunc : public Func {
        double _base;
        std::string _s;
    public:
        /*!
         * Класс для создания экспоненциальной функции
         */
        class ExpFuncCreator : public FuncCreator {
        public:
            /*!
             * Создает экспоненциальную функцию
             * @param args положительное основание
             */
            FuncPtr create(std::any &&args) override {
                return std::make_shared<ExpFunc>(std::any_cast<double>(args));
            }
        };
        /*!
         * Создает экспоненциальную функцию
         * @param base положительное основание
         */
        ExpFunc(double base) : _base(base) {
            if (base <= 0) {
                std::stringstream ss;
                ss << "Non-positive exponent base " << base;
                throw std::domain_error(ss.str());
            }
            std::stringstream ss;
            ss << base << "^x";
            _s = ss.str();
        }
        /*!
         * Вычисляет значение экспоненциальной функции в точке
         * @param x точка
         * @return значение функции
         */
        double operator()(double x) const override {
            return std::pow(_base, x);
        }
        /*!
         * Вычисляет значение производной экспоненциальной функции в точке
         * @param x точка
         * @return значение производной
         */
        double derive(double x) const override {
            return std::pow(_base, x) * std::log(_base);
        }
        /*!
         * Переводит объект в строковое представление
         * @return "основание^x"
         */
        std::string to_string() const override {
            return _s;
        }
    };
}

#endif //MATKIB_EXP_FUNC_H
