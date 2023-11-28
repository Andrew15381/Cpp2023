//
// Created by andrew on 27.11.23.
//

#ifndef MATKIB_IDENT_FUNC_H
#define MATKIB_IDENT_FUNC_H

#include "func.h"

namespace FuncLib {
    /*!
     * Класс для тождественной функции
     */
    class IdentFunc : public Func {
        std::string _s;
    public:
        /*!
         * Класс для создания тождественной функции
         */
        class IdentFuncCreator : public FuncCreator {
        public:
            /*!
             * Создает тождественную функцию
             * @param args не используется
             * @return тождественная функция
             */
            FuncPtr create(std::any &&args) override {
                return std::make_shared<IdentFunc>();
            }
        };
        /*!
         * Создает тождественную функцию
         */
        IdentFunc() : _s("x") {}
        /*!
         * Вычисляет значение тождественной функции в точке x
         * @param x точка
         * @return значение функции
         */
        double operator()(double x) const override {
            return x;
        }
        /*!
         * Вычисляет значение производной тождественной функции в точке x
         * @param x точка
         * @return значение произвоодной
         */
        double derive(double x) const override {
            return 1;
        }
        /*!
         * Переводит объект в строковое представление
         * @return "x"
         */
        std::string to_string() const override {
            return _s;
        }
    };
}

#endif //MATKIB_IDENT_FUNC_H
