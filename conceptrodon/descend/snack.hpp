// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SNACK_H
#define CONCEPTRODON_SNACK_H

#include <type_traits>
#include "conceptrodon/snowfall.hpp"

namespace Conceptrodon {

template<template<template<template<template<typename...> class...> class...> class...> class Silence, size_t I>
struct Snack
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Snowfall<Silence>;

    static constexpr auto lark
    (Snowfall<Silence>) -> std::integral_constant<size_t, I>;
};
 
}

#endif