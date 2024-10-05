// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_TRIP_H
#define CONCEPTRODON_ROADRIVORE_TRIP_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Radio>
struct Trip
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<typename...> class...Songs>
        using Road = Car<typename Radio<Songs...>::type>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Road>::template ProtoRoad<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::value>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Road>::template ProtoRoad<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Mold>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Road>::template ProtoRoad<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Page>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Road>::template ProtoRoad<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Road>::template ProtoSail<Stockrooms...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif