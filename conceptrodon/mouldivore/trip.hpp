// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TRIP_H
#define CONCEPTRODON_MOULDIVORE_TRIP_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Radio>
struct Trip
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<typename...Songs>
        using Mold = Car<typename Radio<Songs...>::type>;

        template<template<typename...> class...Containers>
        using Road = Trip<Mold>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Mold>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::value>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trip<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::template Mold>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trip<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::template Page>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trip<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif