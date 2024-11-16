// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SABER_H
#define CONCEPTRODON_SABER_H

#include <type_traits>
#include "conceptrodon/sailfish.hpp"

namespace Conceptrodon {

template<template<template<template<auto...> class...> class...> class Melancholy, size_t I>
struct Saber
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Sailfish<Melancholy>;

    static constexpr auto lark
    (Sailfish<Melancholy>) -> std::integral_constant<size_t, I>;
};
 
}

#endif