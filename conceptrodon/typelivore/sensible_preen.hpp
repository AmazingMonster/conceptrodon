// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_PREEN_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_PREEN_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensiblePreen
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<typename...> class Cosmetic>
        using Road = Operation<typename Cosmetic<Elements>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif