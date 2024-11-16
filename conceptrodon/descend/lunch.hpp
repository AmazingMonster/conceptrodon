// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LUNCH_H
#define CONCEPTRODON_LUNCH_H

#include <type_traits>
#include "conceptrodon/lungfish.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine, size_t I>
struct Lunch
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Lungfish<Sunshine>;

    static constexpr auto lark
    (Lungfish<Sunshine>) -> std::integral_constant<size_t, I>;
};
 
}

#endif