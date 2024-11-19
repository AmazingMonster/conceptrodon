// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CORAL_H
#define CONCEPTRODON_CORAL_H

#include "conceptrodon/coalfish.hpp"

namespace Conceptrodon {

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency, typename Key>
struct Coral
{ 
    static consteval auto idyl(Key) -> Coalfish<Consistency>;
    static constexpr auto lark(Coalfish<Consistency>) -> Key;
};
 
}

#endif