// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_HABIT_H
#define CONCEPTRODON_HABIT_H

#include "conceptrodon/halfmoon.hpp"

namespace Conceptrodon {

template<template<template<template<template<auto...> class...> class...> class...> class Tranquil, typename Key>
struct Habit
{ 
    static consteval auto idyl(Key) -> Halfmoon<Tranquil>;
    static constexpr auto lark(Halfmoon<Tranquil>) -> Key;
};
 
}

#endif