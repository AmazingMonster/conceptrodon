// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CABIN_H
#define CONCEPTRODON_CABIN_H

#include <type_traits>
#include "conceptrodon/camellia.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance, size_t I>
struct Cabin
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Camellia<Perseverance>;

    static constexpr auto lark
    (Camellia<Perseverance>) -> std::integral_constant<size_t, I>;
};
 
}

#endif