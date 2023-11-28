//
// Created by andrew on 27.11.23.
//

/*!
 * @file
 * Содержит вспомогательные функции для вычисления арифметических выражений.
 * Функции не владеют своими элементами и создаются на стеке без помощи фабрики.
 * Ответственность за память на пользователе.
 */

#ifndef MATKIB_UTIL_FUNC_H
#define MATKIB_UTIL_FUNC_H

#include <stdexcept>
#include <type_traits>
#include "func.h"

namespace FuncLib {
    /*!
     * Базовый класс для составных функций
     */
    class CompositeFunc : public Func {
    protected:
        const Func& _left, &_right;
    public:
        /*!
         * Создает составную функцию
         * @param left первый элемент
         * @param right второй элемент
         */
        CompositeFunc(const Func& left, const Func& right) : _left(left), _right(right) {}
    };

    /*!
     * Составная функция для суммы
     */
    class SumFunc : public CompositeFunc {
        std::string _s;
    public:
        /*!
         * Создает функцию суммы
         * @param left первое слагаемое
         * @param right второе слагаемое
         */
        SumFunc(const Func& left, const Func& right) : CompositeFunc(left, right),
            _s("(" + left.to_string() + ") + (" + right.to_string() + ")") {}
        /*!
         * Вычисляет сумму слагаемых в точке
         * @param x точка
         * @return сумма
         */
        double operator()(double x) const override {
            return _left(x) + _right(x);
        }
        /*!
         * Вычисляет производную суммы в точке
         * @param x точка
         * @return производная суммы
         */
        double derive(double x) const override {
            return _left.derive(x) + _right.derive(x);
        }
        /*!
         * Переводит объект в строковое представление
         * @return "(left) + (right)"
         */
        std::string to_string() const override {
            return _s;
        }
    };

    /*!
     * Составная функция для разности
     */
    class SubFunc : public CompositeFunc {
        std::string _s;
    public:
        /*!
         * Создает функцию разности
         * @param left уменьшаемое
         * @param right вычитаемое
         */
        SubFunc(const Func& left, const Func& right) : CompositeFunc(left, right),
            _s("(" + left.to_string() + ") - (" + right.to_string() + ")") {}
        /*!
         * Вычисляет разность элементов в точке
         * @param x точка
         * @return разность
         */
        double operator()(double x) const override {
            return _left(x) - _right(x);
        }
        /*!
         * Вычисляет производную разности в точке
         * @param x точка
         * @return производная разности
         */
        double derive(double x) const override {
            return _left.derive(x) - _right.derive(x);
        }
        /*!
         * Преобразует объект в строковое представление
         * @return "(left) - (right)"
         */
        std::string to_string() const override {
            return _s;
        }
    };

    /*!
     * Составная функция для частного
     */
    class DivFunc : public CompositeFunc {
        std::string _s;
    public:
        DivFunc(const Func& left, const Func& right) : CompositeFunc(left, right),
            _s("(" + left.to_string() + ") / (" + right.to_string() + ")") {}
        /*!
         * Вычисляет частное элементов в точке
         * @param x точка
         * @return частное
         */
        double operator()(double x) const override {
            if (_right(x) == 0) {
                std::stringstream ss;
                ss << "Zero divisor " << _right.to_string() << " at x=" << x;
                throw std::domain_error(ss.str());
            }
            return _left(x) / _right(x);
        }
        /*!
         * Вычисляет производную частного в точке
         * @param x точка
         * @return производная частного
         */
        double derive(double x) const override {
            return (_left.derive(x) * _right(x) - _right.derive(x) * _left(x)) / _right(x) / _right(x);
        }
        /*!
         * Преобразует объект в строковое представление
         * @return "(left) / (right)"
         */
        std::string to_string() const override {
            return _s;
        }
    };

    /*!
     * Составная функция для произведения
     */
    class MulFunc : public CompositeFunc {
        std::string _s;
    public:
        MulFunc(const Func& left, const Func& right) : CompositeFunc(left, right),
            _s("(" + left.to_string() + ") * (" + right.to_string() + ")") {}
        /*!
         * Вычисляет произведение элементов в точке
         * @param x точка
         * @return произведение
         */
        double operator()(double x) const override {
            return _left(x) * _right(x);
        }
        /*!
         * Вычисляет производную произведения в точке
         * @param x точка
         * @return производная произведения
         */
        double derive(double x) const override {
            return _left.derive(x) * _right(x) + _right.derive(x) * _left(x);
        }
        /*!
         * Преобразует объект в строковое представление
         * @return "(left) * (right)"
         */
        std::string to_string() const override {
            return _s;
        }
    };

    /*!
     * Создает сумму функций (исключение в ином случае)
     * @tparam A тип первого элемента
     * @tparam B тип второго элемента
     * @param left первый элемент
     * @param right второй элемент
     * @return функция суммы
     */
    template<typename A, typename B>
    SumFunc operator+(const A& left, const B& right) {
        if constexpr (std::is_base_of_v<Func, A> && std::is_base_of_v<Func, B>) {
            return SumFunc(left, right);
        } else {
            throw std::logic_error("Unsupported operand types for func sum"); // зачем оно вообще должно компилироваться?
        }
    }

    /*!
     * Создает разность функций (исключение в ином случае)
     * @tparam A тип первого элемента
     * @tparam B тип второго элемента
     * @param left первый элемент
     * @param right второй элемент
     * @return функция разности
     */
    template<typename A, typename B>
    SubFunc operator-(const A& left, const B& right) {
        if constexpr (std::is_base_of_v<Func, A> && std::is_base_of_v<Func, B>) {
            return SubFunc(left, right);
        } else {
            throw std::logic_error("Unsupported operand types for func subtraction");
        }
    }

    /*!
     * Создает частное функций (исключение в ином случае)
     * @tparam A тип первого элемента
     * @tparam B тип второго элемента
     * @param left первый элемент
     * @param right второй элемент
     * @return функция частного
     */
    template<typename A, typename B>
    DivFunc operator/(const A& left, const B& right) {
        if constexpr (std::is_base_of_v<Func, A> && std::is_base_of_v<Func, B>) {
            return DivFunc(left, right);
        } else {
            throw std::logic_error("Unsupported operand types for func division");
        }
    }

    /*!
     * Создает произведение функций (исключение в ином случае)
     * @tparam A тип первого элемента
     * @tparam B тип второго элемента
     * @param left первый элемент
     * @param right второй элемент
     * @return функция произведения
     */
    template<typename A, typename B>
    MulFunc operator*(const A& left, const B& right) {
        if constexpr (std::is_base_of_v<Func, A> && std::is_base_of_v<Func, B>) {
            return MulFunc(left, right);
        } else {
            throw std::logic_error("Unsupported operand types for func multiplication");
        }
    }
}

#endif //MATKIB_UTIL_FUNC_H
