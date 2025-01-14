#ifndef MILODY_LAZY_H
#define MILODY_LAZY_H

#include <functional>

namespace milody::util {

template <class T>
class Lazy {
public:
    Lazy(const std::function<T()>& create) : initialized(false), valueStore(), factory(create) {
    }

    const T& Get() {
        InitValue();
        return valueStore;
    }

    Lazy& operator=(const T& value) {
        InitValue();
        valueStore = value;
        return *this;
    }

    Lazy& operator=(T&& value) {
        InitValue();
        valueStore = value;
        return *this;
    }

private:
    Lazy(const Lazy&) = delete;
    Lazy(Lazy&&) = delete;
    Lazy& operator=(const Lazy&) = delete;
    Lazy& operator=(Lazy&&) = delete;

    void InitValue() {
        mutex.lock();
        if (!initialized) {
            valueStore = factory();
            initialized = true;
        }
        mutex.unlock();
    }

    std::mutex mutex;
    bool initialized;
    T valueStore;
    const std::function<T()> factory;
};

} // namespace milody::util

#endif //MILODY_MILODY_LAZY_H
