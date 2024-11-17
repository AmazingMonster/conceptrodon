// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_DAIRY_H
#define CONCEPTRODON_DAIRY_H

#include <type_traits>
#include "conceptrodon/daydream.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight, size_t I>
struct Dairy
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Daydream<Sunlight>;

    static constexpr auto lark
    (Daydream<Sunlight>) -> std::integral_constant<size_t, I>;
};
 
}

#endif