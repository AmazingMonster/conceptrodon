// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SENSIBLE_PLUME_H
#define CONCEPTRODON_VARYBIVORE_SENSIBLE_PLUME_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Variables>...>;
        };

        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Variables>...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto Variable>
struct SensiblePlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<auto...> class...Cosmetics>
        using Rail = Operation<Cosmetics<Variable>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

#endif