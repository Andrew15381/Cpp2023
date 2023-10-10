#include <iostream>
#include <memory>
#include <functional>
using namespace std;

class A {
public:
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

template <class T>
struct Allocator {
    typedef T value_type;

    std::function<void*(size_t)> _new;
    std::function<void(void*, size_t)> _delete;

    Allocator() : _new(T::operator new), _delete(T::operator delete) {}
    template <class U>
    Allocator (const Allocator<U>& other) {
        _new = other._new;
        _delete = other._delete;
    }
    T* allocate (std::size_t n) {
        return reinterpret_cast<T*>(_new(n * sizeof(T)));
    }
    void deallocate (T* p, std::size_t n) {
        return _delete(p, n);
    }
};

int main() {
    auto sp = std::allocate_shared<A>(Allocator<A>());
    return 0;
}
