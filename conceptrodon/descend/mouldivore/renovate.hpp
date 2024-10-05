// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RENOVATE_H
#define CONCEPTRODON_MOULDIVORE_RENOVATE_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Decorations>
struct Renovate
{
    template<typename...Elements>
    struct ProtoMold 
    { using type = Capsule<Decorations<Elements>...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Capsule<Decorations<Elements>...>;
};

}}

#endif