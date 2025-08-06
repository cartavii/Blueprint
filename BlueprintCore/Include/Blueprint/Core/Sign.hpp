#ifndef BLUEPRINT_CORE_SIGN_HPP
#define BLUEPRINT_CORE_SIGN_HPP

namespace Blueprint::Core {
template<typename T>
T sign(T x);

float signF(float x);

double signD(double x);

int signI(float x);
} // Blueprint::Core

template<typename T>
T Blueprint::Core::sign(T x) {
    const T zero = static_cast<T>(0);
    if (x > zero) {
        return static_cast<T>(1);
    }
    if (x < zero) {
        return static_cast<T>(-1);
    }
    return zero;
}

#endif // BLUEPRINT_CORE_SIGN_HPP
