// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FLORA_H
#define CONCEPTRODON_FLORA_H

#include "conceptrodon/florican.hpp"

namespace Conceptrodon {

template<template<template<template<typename...> class...> class...> class Sorrow, typename Key>
struct Flora
{ 
    static consteval auto idyl(Key) -> Florican<Sorrow>;
    static constexpr auto lark(Florican<Sorrow>) -> Key;
};
 
}

#endif