// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_DAIRY_H
#define CONCEPTRODON_DAIRY_H

#include "conceptrodon/daydream.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight, typename Key>
struct Dairy
{ 
    static consteval auto idyl(Key) -> Daydream<Sunlight>;
    static constexpr auto lark(Daydream<Sunlight>) -> Key;
};
 
}

#endif