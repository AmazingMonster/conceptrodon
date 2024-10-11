// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TREK_H
#define CONCEPTRODON_PAGELIVORE_TREK_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Radio>
struct Trek
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>>;

        template<template<typename...> class...Containers>
        using Road = Trek<Page>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Page>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Page>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Page>::template ProtoSnow<Foolishness...>;
        
        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Page>::template ProtoHail<Foolishness...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::value>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Page>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Page>::template ProtoSnow<Foolishness...>;
        
        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Page>::template ProtoHail<Foolishness...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::template Mold>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Page>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Page>::template ProtoSnow<Foolishness...>;
        
        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Page>::template ProtoHail<Foolishness...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::template Page>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Page>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Page>::template ProtoSnow<Foolishness...>;
        
        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Page>::template ProtoHail<Foolishness...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

    template<template<template<template<typename...> class...> class...> class Car>
    struct ProtoSnow
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::template Road>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Page>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Page>::template ProtoSnow<Foolishness...>;
        
        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Page>::template ProtoHail<Foolishness...>;
    };
    
    template<template<template<template<typename...> class...> class...> class...Foolishness>
    using Snow = ProtoSnow<Foolishness...>;

    template<template<template<template<auto...> class...> class...> class Car>
    struct ProtoHail
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::template Rail>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Page>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Foolishness>
        using Snow = Trek<Page>::template ProtoSnow<Foolishness...>;
        
        template<template<template<template<auto...> class...> class...> class...Foolishness>
        using Hail = Trek<Page>::template ProtoHail<Foolishness...>;
    };
    
    template<template<template<template<auto...> class...> class...> class...Foolishness>
    using Hail = ProtoHail<Foolishness...>;
};

}}

#endif