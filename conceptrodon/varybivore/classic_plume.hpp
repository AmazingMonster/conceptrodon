// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_CLASSIC_PLUME_H
#define CONCEPTRODON_VARYBIVORE_CLASSIC_PLUME_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct ClassicPlume
{
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<typename Cosmetics<Variables>::type...>;
    };

    template<template<auto...> class Cosmetic>
    struct ProtoRail<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<typename Cosmetic<Variables>::type...>;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct ClassicPlume<Variable>
{
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variable>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation<typename Cosmetics<Variable>::type...>;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

}}

#endif