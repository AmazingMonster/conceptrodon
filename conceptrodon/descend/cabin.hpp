// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CABIN_H
#define CONCEPTRODON_CABIN_H

#include "conceptrodon/camellia.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance, typename Key>
struct Cabin
{ 
    static consteval auto idyl(Key) -> Camellia<Perseverance>;
    static constexpr auto lark(Camellia<Perseverance>) -> Key;
};
 
}

#endif