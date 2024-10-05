// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_PLUME_H
#define CONCEPTRODON_VARYBIVORE_PLUME_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Plume
{
    template<template<auto...> class...Cosmetics>
    struct ProtoRail
    { using type = Capsule<typename Cosmetics<Variables>::type...>; };

    template<template<auto...> class...Cosmetics>
    using Rail= ProtoRail<Cosmetics...>;

    template<template<auto...> class...Cosmetics>
    using Rail_t = Capsule<typename Cosmetics<Variables>::type...>;
};

}}

#endif