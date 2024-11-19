// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROVER_H
#define CONCEPTRODON_ROVER_H

#include "conceptrodon/delegacy.hpp"

namespace Conceptrodon {

template<template<template<typename...> class...> class Warehouse, typename Key>
struct Rover
{ 
    static consteval auto idyl(Key) -> Delegacy<Warehouse>;
    static constexpr auto lark(Delegacy<Warehouse>) -> Key;
};
 
}

#endif