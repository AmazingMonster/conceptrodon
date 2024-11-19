// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GRAPE_H
#define CONCEPTRODON_GRAPE_H

#include "conceptrodon/graphite.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine, typename Key>
struct Grape
{ 
    static consteval auto idyl(Key) -> Graphite<Sunshine>;
    static constexpr auto lark(Graphite<Sunshine>) -> Key;
};
 
}

#endif