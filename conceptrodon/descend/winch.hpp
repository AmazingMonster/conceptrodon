// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_WINCH_H
#define CONCEPTRODON_WINCH_H

#include <type_traits>
#include "conceptrodon/wildfire.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine, size_t I>
struct Winch
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Wildfire<Sunshine>;

    static constexpr auto lark
    (Wildfire<Sunshine>) -> std::integral_constant<size_t, I>;
};
 
}

#endif