// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_HABIT_H
#define CONCEPTRODON_HABIT_H

#include <type_traits>
#include "conceptrodon/halfmoon.hpp"

namespace Conceptrodon {

template<template<template<template<template<auto...> class...> class...> class...> class Tranquil, size_t I>
struct Habit
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Halfmoon<Tranquil>;

    static constexpr auto lark
    (Halfmoon<Tranquil>) -> std::integral_constant<size_t, I>;
};
 
}

#endif