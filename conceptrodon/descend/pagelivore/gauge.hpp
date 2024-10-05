// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_GAUGE_H
#define CONCEPTRODON_PAGELIVORE_GAUGE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Devices>
struct Gauge
{
    template<auto...Variables>
    struct ProtoPage 
    { using type = Shuttle<Devices<Variables>::value...>; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = Shuttle<Devices<Variables>::value...>;
};

}}

#endif