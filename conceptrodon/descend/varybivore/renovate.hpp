// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_RENOVATE_H
#define CONCEPTRODON_VARYBIVORE_RENOVATE_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Renovate
{
    template<template<auto...> class...Decorations>
    struct ProtoRail 
    { using type = Capsule<Decorations<Variables>...>; };

    template<template<auto...> class...Decorations>
    using Rail = ProtoRail<Decorations...>;

    template<template<auto...> class...Decorations>
    using Rail_t = Capsule<Decorations<Variables>...>;
};

}}

#endif