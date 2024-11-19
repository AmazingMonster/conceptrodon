// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_WINCH_H
#define CONCEPTRODON_WINCH_H

#include "conceptrodon/wildfire.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine, typename Key>
struct Winch
{ 
    static consteval auto idyl(Key) -> Wildfire<Sunshine>;
    static constexpr auto lark(Wildfire<Sunshine>) -> Key;
};
 
}

#endif