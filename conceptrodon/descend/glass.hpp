// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GLASS_H
#define CONCEPTRODON_GLASS_H

#include <type_traits>
#include "conceptrodon/glowworm.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight, size_t I>
struct Glass
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Glowworm<Sunlight>;

    static constexpr auto lark
    (Glowworm<Sunlight>) -> std::integral_constant<size_t, I>;
};
 
}

#endif