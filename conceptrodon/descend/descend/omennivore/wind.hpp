// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_WIND_H
#define CONCEPTRODON_OMENNIVORE_WIND_H

#include "conceptrodon/descend/omennivore/breeze.hpp"
#include "conceptrodon/omennivore/concepts/flow_probe.hpp"
#include "conceptrodon/omennivore/concepts/sail_probe.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Melody>
struct Wind: public Breeze<Melody> {};

template<typename Melody>
requires FlowProbe<Melody>
struct Wind<Melody>: public Breeze<Melody> 
{
    template<template<template<typename...> class...> class...Tunes>
    using Flow = Melody::template Flow<Tunes...>;
};

template<typename Melody>
requires SailProbe<Melody>
struct Wind<Melody>: public Breeze<Melody>
{
    template<template<template<auto...> class...> class...Tunes>
    using Sail = Melody::template Sail<Tunes...>;
};

template<typename Melody>
requires FlowProbe<Melody>
&& SailProbe<Melody>
struct Wind<Melody>: public Breeze<Melody>
{
    template<template<template<typename...> class...> class...Tunes>
    using Flow = Melody::template Flow<Tunes...>;

    template<template<template<auto...> class...> class...Tunes>
    using Sail = Melody::template Sail<Tunes...>;
};

}}

#endif