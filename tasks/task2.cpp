#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <strstream>
using namespace std;

// задача 1: std::vector<bool>, т.к. возвращает prvalue обертку для ссылки на один бит, далее задача 2

struct TPrettyPrinter {
    mutable std::strstream stream;
    std::string Str() const {
        return stream.str();
    }
    template<class T>
    TPrettyPrinter& Format(const T& s) {
        stream << s;
        return *this;
    }
    template<class U, class V>
    TPrettyPrinter& Format(const std::pair<U, V>& p) {
        stream << '(';
        Format(p.first);
        stream << ", ";
        Format(p.second);
        stream << ')';
        return *this;
    }
    template<class T>
    TPrettyPrinter& Format(const std::vector<T>& v) {
        stream << "[";
        for (int i = 0; i < v.size() - 1; ++i) {
            Format(v[i]);
            stream << ", ";
        }
        Format(v[v.size() - 1]);
        stream << "]";
        return *this;
    }
    template<class T>
    TPrettyPrinter& Format(const std::set<T>& s) {
        stream << "{";
        for (int i = 0; i < s.size() - 1; ++i) {
            Format(s[i]);
            stream << ", ";
        }
        Format(s[s.size() - 1]);
        stream << "}";
        return *this;
    }
    template<class ...T>
    TPrettyPrinter& Format(const std::tuple<T...>& t) {
        FormatTupleImpl(t, std::make_index_sequence<sizeof...(T)>());
        return *this;
    }
private:
    template<class T, size_t... I>
    void FormatTupleImpl(const T& t, std::index_sequence<I...>) {
        stream << '(';
        ((stream << (I == 0 ? "" : ", "), Format(std::get<I>(t))), ...);
        stream << ')';
    }
};

template<typename T>
std::string Format(const T& t) {
    return TPrettyPrinter().Format(t).Str();
}

int main() {
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
    std::string s1 = TPrettyPrinter().Format("vector: ").Format(v).Str();
    // "vector: [(1, 4), (5, 6)]"
    std::string s2 = TPrettyPrinter().Format(t).Format(" ! ").Format(0).Str();
    // "(xyz, 1, 2) ! 0"
    std::cout << s1 << '\n' << s2;
}
