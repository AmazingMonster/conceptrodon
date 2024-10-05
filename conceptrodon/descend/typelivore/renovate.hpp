// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_RENOVATE_H
#define CONCEPTRODON_TYPELIVORE_RENOVATE_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Renovate
{
    template<template<typename...> class...Decorations>
    struct ProtoRoad
    { using type = Capsule<Decorations<Elements>...>; };

    template<template<typename...> class...Decorations>
    using Road = ProtoRoad<Decorations...>;

    template<template<typename...> class...Decorations>
    using Road_t = Capsule<Decorations<Elements>...>;
};

}}

#endif