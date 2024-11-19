// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAMEN_H
#define CONCEPTRODON_RAMEN_H

#include "conceptrodon/legation.hpp"

namespace Conceptrodon {

template<template<template<auto...> class...> class Stockroom, typename Key>
struct Ramen
{ 
    static consteval auto idyl(Key) -> Legation<Stockroom>;
    static constexpr auto lark(Legation<Stockroom>) -> Key;
};
 
}

#endif