// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SABER_H
#define CONCEPTRODON_SABER_H

#include "conceptrodon/sailfish.hpp"

namespace Conceptrodon {

template<template<template<template<auto...> class...> class...> class Melancholy, typename Key>
struct Saber
{ 
    static consteval auto idyl(Key) -> Sailfish<Melancholy>;
    static constexpr auto lark(Sailfish<Melancholy>) -> Key;
};
 
}

#endif