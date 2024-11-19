// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TOTEM_H
#define CONCEPTRODON_TOTEM_H

#include "conceptrodon/emissary.hpp"

namespace Conceptrodon {

template<template<typename...> class Container, typename Key>
struct Totem
{ 
    static consteval auto idyl(Key) -> Emissary<Container>;
    static constexpr auto lark(Emissary<Container>) -> Key;
};
 
}

#endif