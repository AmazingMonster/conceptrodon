// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_METAMORPHOSE_H
#define CONCEPTRODON_MOULDIVORE_METAMORPHOSE_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Metamorphose
{
    template<template<typename...> class Puberty>
    struct ProtoRoad
    {
        struct Slash
        {
            template<template<typename...> class Acne>
            struct ProtoRoad
            {
                template<typename Element>
                struct Hidden 
                { using type = Element; };

                template<typename Element>
                requires Puberty<Element>::value
                struct Hidden<Element>
                { using type = Acne<Element>; };

                template<typename...Elements>
                using Mold = Operation<typename Hidden<Elements>::type...>;
            };
        };

        template<template<typename...> class...Agreements>
        using Road = Slash::template ProtoRoad<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif