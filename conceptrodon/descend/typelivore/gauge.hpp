// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_GAUGE_H
#define CONCEPTRODON_TYPELIVORE_GAUGE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Gauge
{
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { using type = Shuttle<Devices<Elements>::value...>; };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;

    template<template<typename...> class...Devices>
    using Road_t = Shuttle<Devices<Elements>::value...>;
};

}}

#endif