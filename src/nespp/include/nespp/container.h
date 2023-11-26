/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include "types.h"

namespace nespp {
    template<class T>
    concept Container = requires(T t, T::data_type val) {
        {t.begin()} -> Iterable;
        {t.end()} -> Iterable;
        {t.contains(val)} -> Convertible<bool>;
        {t.empty()} -> Convertible<bool>;
        {t.size()} -> Convertible<size_t>;
        {t.capacity()} -> Convertible<size_t>;
    };

    template <Container C, class LAMBDA>
    auto constexpr container_any(C container, LAMBDA && lambda) {
        for(auto & value : container) {
            if(lambda(value)) return true;
        }
        return false;
    }
    template <Container C, class LAMBDA>
    auto constexpr container_all(C container, LAMBDA && lambda) {
        for(auto & value : container) {
            if(!lambda(value)) return false;
        }
        return true;
    }

}