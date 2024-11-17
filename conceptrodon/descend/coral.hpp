// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CORAL_H
#define CONCEPTRODON_CORAL_H

#include <type_traits>
#include "conceptrodon/coalfish.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency, size_t I>
struct Coral
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Coalfish<Consistency>;

    static constexpr auto lark
    (Coalfish<Consistency>) -> std::integral_constant<size_t, I>;
};
 
}

#endif