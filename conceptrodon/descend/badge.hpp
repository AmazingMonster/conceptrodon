// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_BADGE_H
#define CONCEPTRODON_BADGE_H

#include "conceptrodon/diplomat.hpp"

namespace Conceptrodon {

template<template<auto...> class Sequence, typename Key>
struct Badge
{ 
    static consteval auto idyl(Key) -> Diplomat<Sequence>;
    static constexpr auto lark(Diplomat<Sequence>) -> Key;
};
 
}

#endif