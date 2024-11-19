// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SNACK_H
#define CONCEPTRODON_SNACK_H

#include "conceptrodon/snowfall.hpp"

namespace Conceptrodon {

template<template<template<template<template<typename...> class...> class...> class...> class Silence, typename Key>
struct Snack
{ 
    static consteval auto idyl(Key) -> Snowfall<Silence>;
    static constexpr auto lark(Snowfall<Silence>) -> Key;
};
 
}

#endif