//
// Created by andrew on 27.11.23.
//

#ifndef MATKIB_FUNC_H
#define MATKIB_FUNC_H

#include <memory>
#include <string>
#include <unordered_map>
#include <any>

namespace FuncLib {
    /*!
     * Базовый класс для функций
     */
    class Func {
        class FuncFactory;
    public:
        static FuncFactory _factory;
        /*!
         * Вычисляет значение функции в точке x
         * @param x точка
         * @return значение функции
         */
        virtual double operator()(double x) const = 0;
        /*!
         * Вычисляет значение производной функции в точке x
         * @param x точка
         * @return значение производной
         */
        virtual double derive(double x) const = 0;
        /*!
         * Переводит объект в строковое представление
         * @return строка
         */
        virtual std::string to_string() const = 0;
        virtual ~Func() {}
    };
    using FuncPtr = std::shared_ptr<Func>;

    /*!
     * Базовый класс для создания функций
     */
    class FuncCreator {
    public:
        /*!
         * Создает функцию
         * @param args параметры функции
         * @return функция
         */
        virtual FuncPtr create(std::any &&args) = 0;
    };
    using FuncCreatorPtr = std::shared_ptr<FuncCreator>;
}

#include "const_func.h"
#include "ident_func.h"
#include "polynomial_func.h"
#include "power_func.h"
#include "exp_func.h"
#include "util_func.h"

namespace FuncLib {
    /*!
     * Класс для создания функций по названию
     */
    class Func::FuncFactory {
        std::unordered_map<std::string, FuncCreatorPtr> _creators;
    public:
        /*!
         * Создает фабрику, регистрирует элементарные функции
         */
        FuncFactory() {
            register_creator("const",
                             std::static_pointer_cast<FuncCreator>(std::make_shared<ConstFunc::ConstFuncCreator>()));
            register_creator("ident",
                             std::static_pointer_cast<FuncCreator>(std::make_shared<IdentFunc::IdentFuncCreator>()));
            register_creator("power",
                             std::static_pointer_cast<FuncCreator>(std::make_shared<PowerFunc::PowerFuncCreator>()));
            register_creator("polynomial",
                             std::static_pointer_cast<FuncCreator>(std::make_shared<PolynomialFunc::PolynomialFuncCreator>()));
            register_creator("exp",
                             std::static_pointer_cast<FuncCreator>(std::make_shared<ExpFunc::ExpFuncCreator>()));
        }
        /*!
         * Регистрирует класс для создания функций по имени
         * @param name имя функции
         * @param creator класс для создания
         */
        void register_creator(const std::string &name, FuncCreatorPtr creator) {
            _creators[name] = creator;
        }
        /*!
         * Создает функцию по имени
         * @param name имя функции
         * @param args параметры создания функции
         * @return функция
         */
        FuncPtr create(const std::string &name, std::any &&args = std::any()) {
            return _creators[name]->create(std::forward<std::any>(args));
        }
    };

    Func::FuncFactory Func::_factory;

    /*!
     * Решает уравнение f=0 методом градиентного спуска
     * @param func функция
     * @param x_0 начальное приближение
     * @param lr шаг
     * @param iter_count количество итераций
     * @return найденное решение
     */
    double solve(const Func& func, double x_0, double lr, size_t iter_count) {
        double x = x_0;
        for (size_t i = 0; i < iter_count; ++i) {
            x -= lr * func.derive(x);
        }
        return x;
    }
}

#endif //MATKIB_FUNC_H
