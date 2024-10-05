// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_GRADE_H
#define CONCEPTRODON_MOULDIVORE_GRADE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Paper>
struct Grade
{
    template<typename...Elements>
    struct ProtoMold 
    { using type = Shuttle<Paper<Elements>::value...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = Shuttle<Paper<Elements>::value...>;
};

}}

#endif