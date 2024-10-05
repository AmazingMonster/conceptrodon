// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_REFURBISH_H
#define CONCEPTRODON_VARYBIVORE_REFURBISH_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Refurbish
{
    template<template<auto...> class Decoration>
    struct ProtoRail 
    { using type = Capsule<Decoration<Variables>...>; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class...Args>
    using Rail_t = ProtoRail<Args...>::type;

    template<template<auto...> class Decoration>
    using UniRail = Capsule<Decoration<Variables>...>;
};

}}

#endif