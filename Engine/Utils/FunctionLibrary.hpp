#ifndef PE_FUNCTION_LIBRARY_HPP
#define PE_FUNCTION_LIBRARY_HPP

#include <type_traits>

template <typename T, typename U>
bool IsA(const U& Object) {
    return std::is_same<T, U>::value;
}

template <typename T, typename U>
T Cast(U Object) {
    return dynamic_cast<T>(Object);
}

template <typename T, typename U>
T ForceCast(U Object) {
    return (T) Object;
}

#endif