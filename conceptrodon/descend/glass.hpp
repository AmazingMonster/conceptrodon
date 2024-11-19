// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GLASS_H
#define CONCEPTRODON_GLASS_H

#include "conceptrodon/glowworm.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight, typename Key>
struct Glass
{ 
    static consteval auto idyl(Key) -> Glowworm<Sunlight>;
    static constexpr auto lark(Glowworm<Sunlight>) -> Key;
};
 
}

#endif