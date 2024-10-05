// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_PLUME_H
#define CONCEPTRODON_MOULDIVORE_PLUME_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Cosmetics>
struct Plume
{
    template<typename...Elements>
    struct ProtoMold 
    { using type = Capsule<typename Cosmetics<Elements>::type...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Capsule<typename Cosmetics<Elements>::type...>;
};

}}

#endif