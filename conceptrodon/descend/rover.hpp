// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROVER_H
#define CONCEPTRODON_ROVER_H

#include <type_traits>
#include "conceptrodon/delegacy.hpp"

namespace Conceptrodon {

template<template<template<typename...> class...> class Warehouse, size_t I>
struct Rover
{ 
    static consteval auto idyl
    (std::integral_constant<size_t, I>) -> Delegacy<Warehouse>;

    static constexpr auto lark
    (Delegacy<Warehouse>) -> std::integral_constant<size_t, I>;
};
 
}

#endif