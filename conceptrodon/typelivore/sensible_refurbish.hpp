// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_REFURBISH_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_REFURBISH_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensibleRefurbish
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    { 
        template<template<typename...> class Decoration>
        using Road = Operation<Decoration<Elements>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif