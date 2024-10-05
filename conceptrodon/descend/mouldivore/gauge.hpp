// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_GAUGE_H
#define CONCEPTRODON_MOULDIVORE_GAUGE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Devices>
struct Gauge
{
    template<typename...Elements>
    struct ProtoMold 
    { using type = Shuttle<Devices<Elements>::value...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Shuttle<Devices<Elements>::value...>;
};

}}

#endif