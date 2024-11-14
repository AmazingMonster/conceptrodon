// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_BADGE_H
#define CONCEPTRODON_BADGE_H

#include <type_traits>
#include "conceptrodon/diplomat.hpp"

namespace Conceptrodon {

template<template<auto...> class Sequence, size_t I>
struct Badge
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Diplomat<Sequence>;

    static constexpr auto lark
    (Diplomat<Sequence>) -> std::integral_constant<size_t, I>;
};
 
}

#endif