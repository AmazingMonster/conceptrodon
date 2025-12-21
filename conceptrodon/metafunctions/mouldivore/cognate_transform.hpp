// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_TRANSFORM_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_TRANSFORM_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateTransform
{
    template<template<typename...> class...Puberty>
    struct ProtoRoad
    {
        struct Slash
        {
            template<template<typename...> class...Hormones>
            struct ProtoRoad
            {
                template<template<typename...> class Hormone, typename Element>
                struct Detail
                { using type = Element; };

                template<template<typename...> class Hormone, typename Element>
                requires (...&&Puberty<Element>::value)
                struct Detail<Hormone, Element>
                { using type = Hormone<Element>; };

                template<typename...Elements>
                struct Hidden 
                { using type = Operation<typename Detail<Hormones, Elements>::type...>; };

                template<typename Element>
                struct Hidden<Element>
                { using type = Operation<typename Detail<Hormones, Element>::type...>; };

                template<typename...Elements>
                using Mold = Hidden<Elements...>::type;
            };

            template<template<typename...> class Hormone>
            struct ProtoRoad<Hormone>
            {
                template<typename Element>
                struct Detail
                { using type = Element; };

                template<typename Element>
                requires (...&&Puberty<Element>::value)
                struct Detail<Element>
                { using type = Hormone<Element>; };

                template<typename...Elements>
                using Mold = Operation<typename Detail<Elements>::type...>;
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