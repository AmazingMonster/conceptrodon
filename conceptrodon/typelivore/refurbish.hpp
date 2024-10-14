// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_REFURBISH_H
#define CONCEPTRODON_TYPELIVORE_REFURBISH_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Refurbish
{
    template<template<typename...> class Decoration>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Decoration<Elements>...>; 
        }; 

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<Decoration<Elements>...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif