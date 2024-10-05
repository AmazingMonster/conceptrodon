// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_PREEN_H
#define CONCEPTRODON_MOULDIVORE_PREEN_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Cosmetic>
struct Preen
{
    template<typename...Elements>
    struct ProtoMold 
    { using type = Capsule<typename Cosmetic<Elements>::type...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Capsule<typename Cosmetic<Elements>::type...>;
};

}}

#endif