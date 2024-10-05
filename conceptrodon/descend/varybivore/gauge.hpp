// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_GAUGE_H
#define CONCEPTRODON_VARYBIVORE_GAUGE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Gauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail 
    { using type = Shuttle<Devices<Variables>::value...>; };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;

    template<template<auto...> class...Devices>
    using Rail_t = Shuttle<Devices<Variables>::value...>;
};

}}

#endif