// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_REFURBISH_H
#define CONCEPTRODON_MOULDIVORE_REFURBISH_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Decoration>
struct Refurbish
{
    template<typename...Elements>
    struct ProtoMold 
    { using type = Capsule<Decoration<Elements>...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Capsule<Decoration<Elements>...>;
};

}}

#endif