// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TOTEM_H
#define CONCEPTRODON_TOTEM_H

#include <type_traits>
#include "conceptrodon/emissary.hpp"

namespace Conceptrodon {

template<template<typename...> class Container, size_t I>
struct Totem
{ 
    static consteval auto idyl(std::integral_constant<size_t, I>)
    -> Emissary<Container>;

    static constexpr size_t lark(Emissary<Container>)
    { return I; }
};
 
}

#endif