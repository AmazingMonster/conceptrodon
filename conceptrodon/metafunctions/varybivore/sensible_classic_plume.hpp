// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SENSIBLE_CLASSIC_PLUME_H
#define CONCEPTRODON_VARYBIVORE_SENSIBLE_CLASSIC_PLUME_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Variables>::type...>;
        };

        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Variables>::type...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <typename Cosmetics<Variable>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif