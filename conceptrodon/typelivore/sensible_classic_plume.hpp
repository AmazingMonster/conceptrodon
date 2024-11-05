// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_CLASSIC_PLUME_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_CLASSIC_PLUME_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Elements>::type...>;
        };

        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<typename Element>
struct SensibleClassicPlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<template<typename...> class...Cosmetics>
        using Road = Operation<typename Cosmetics<Element>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif