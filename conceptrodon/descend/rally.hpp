// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RALLY_H
#define CONCEPTRODON_RALLY_H

#include <type_traits>
#include "conceptrodon/legation.hpp"

namespace Conceptrodon {

template<template<template<auto...> class...> class Stockroom, size_t I>
struct Rally
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Legation<Stockroom>;

    static constexpr auto lark
    (Legation<Stockroom>) -> std::integral_constant<size_t, I>;
};
 
}

#endif