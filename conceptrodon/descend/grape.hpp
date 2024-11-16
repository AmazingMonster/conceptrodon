// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GRAPE_H
#define CONCEPTRODON_GRAPE_H

#include <type_traits>
#include "conceptrodon/graphite.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine, size_t I>
struct Grape
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Graphite<Sunshine>;

    static constexpr auto lark
    (Graphite<Sunshine>) -> std::integral_constant<size_t, I>;
};
 
}

#endif