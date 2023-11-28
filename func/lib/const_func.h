//
// Created by andrew on 27.11.23.
//

#ifndef MATKIB_CONST_FUNC_H
#define MATKIB_CONST_FUNC_H

#include <sstream>
#include "func.h"

namespace FuncLib {
    /*!
     * Класс для константной функции
     */
    class ConstFunc : public Func {
        double _c;
        std::string _s;
    public:
        /*!
         * Класс для создания константной функции
         */
        class ConstFuncCreator : public FuncCreator {
        public:
            /*!
             * Создает константную функцию
             * @param args константа
             * @return константная функция
             */
            FuncPtr create(std::any &&args) override {
                return std::make_shared<ConstFunc>(std::any_cast<double>(args));
            }
        };
        /*!
         * Создает константную функцию
         * @param c константа
         */
        ConstFunc(double c) : _c(c) {
            std::stringstream ss;
            ss << _c;
            _s = ss.str();
        }
        /*!
         * Вычисляет значение константной функции в точке x
         * @param x точка
         * @return значение функции
         */
        double operator()(double x) const override {
            return _c;
        }
        /*!
         * Вычисляет значение производной константной функции в точке x
         * @param x точка
         * @return значение произвоодной
         */
        double derive(double x) const override {
            return 0;
        }
        /*!
         * Переводит объект в строковое представление
         * @return строковое представление константы
         */
        std::string to_string() const override {
            return _s;
        }
    };
}

#endif //MATKIB_CONST_FUNC_H
