// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_TREK_H
#define CONCEPTRODON_ROADRIVORE_TREK_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Radio>
struct Trek
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>>;

        template<template<typename...> class...Containers>
        using SubRoad = Trek<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Road>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Road>::template ProtoSnow<Foolishness...>;

        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Road>::template ProtoHail<Foolishness...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::value>;

        template<template<typename...> class...Containers>
        using SubRoad = Trek<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Road>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Road>::template ProtoSnow<Foolishness...>;

        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Road>::template ProtoHail<Foolishness...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Mold>;

        template<template<typename...> class...Containers>
        using SubRoad = Trek<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Road>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Road>::template ProtoSnow<Foolishness...>;

        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Road>::template ProtoHail<Foolishness...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Page>;

        template<template<typename...> class...Containers>
        using SubRoad = Trek<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Road>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Road>::template ProtoSnow<Foolishness...>;

        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Road>::template ProtoHail<Foolishness...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

    template<template<template<template<typename...> class...> class...> class Car>
    struct ProtoSnow
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Road>;

        template<template<typename...> class...Containers>
        using SubRoad = Trek<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Road>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Road>::template ProtoSnow<Foolishness...>;

        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Road>::template ProtoHail<Foolishness...>;
    };
    
    template<template<template<template<typename...> class...> class...> class...Foolishness>
    using Snow = ProtoSnow<Foolishness...>;

    template<template<template<template<auto...> class...> class...> class Car>
    struct ProtoHail
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Rail>;

        template<template<typename...> class...Containers>
        using SubRoad = Trek<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Road>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Road>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Road>::template ProtoSnow<Foolishness...>;

        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Road>::template ProtoHail<Foolishness...>;
    };
    
    template<template<template<template<auto...> class...> class...> class...Foolishness>
    using Hail = ProtoHail<Foolishness...>;
};

}}

#endif