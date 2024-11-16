// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FLORA_H
#define CONCEPTRODON_FLORA_H

#include <type_traits>
#include "conceptrodon/florican.hpp"

namespace Conceptrodon {

template<template<template<template<typename...> class...> class...> class Sorrow, size_t I>
struct Flora
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Florican<Sorrow>;

    static constexpr auto lark
    (Florican<Sorrow>) -> std::integral_constant<size_t, I>;
};
 
}

#endif