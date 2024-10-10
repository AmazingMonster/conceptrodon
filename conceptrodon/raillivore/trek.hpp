// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_TREK_H
#define CONCEPTRODON_RAILLIVORE_TREK_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Radio>
struct Trek
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<auto...> class...Songs>
        using Rail = Car<Radio<Songs...>>;

        template<template<auto...> class...Sequences>
        using SubRail = Trek<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Rail>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Rail>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Rail>::template ProtoZeal<Madness...>;
    
        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Rail>::template ProtoZest<Craziness...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<auto...> class...Songs>
        using Rail = Car<Radio<Songs...>::value>;

        template<template<auto...> class...Sequences>
        using SubRail = Trek<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Rail>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Rail>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Rail>::template ProtoZeal<Madness...>;
    
        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Rail>::template ProtoZest<Craziness...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<auto...> class...Songs>
        using Rail = Car<Radio<Songs...>::template Mold>;

        template<template<auto...> class...Sequences>
        using SubRail = Trek<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Rail>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Rail>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Rail>::template ProtoZeal<Madness...>;
    
        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Rail>::template ProtoZest<Craziness...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<auto...> class...Songs>
        using Rail = Car<Radio<Songs...>::template Page>;

        template<template<auto...> class...Sequences>
        using SubRail = Trek<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Rail>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Rail>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Rail>::template ProtoZeal<Madness...>;
    
        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Rail>::template ProtoZest<Craziness...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

    template<template<template<template<typename...> class...> class...> class Car>
    struct ProtoZeal
    {
        template<template<auto...> class...Songs>
        using Rail = Car<Radio<Songs...>::template Road>;

        template<template<auto...> class...Sequences>
        using SubRail = Trek<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Rail>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Rail>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Rail>::template ProtoZeal<Madness...>;
    
        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Rail>::template ProtoZest<Craziness...>;
    };
    
    template<template<template<template<typename...> class...> class...> class...Madness>
    using Zeal = ProtoZeal<Madness...>;

    template<template<template<template<auto...> class...> class...> class Car>
    struct ProtoZest
    {
        template<template<auto...> class...Songs>
        using Rail = Car<Radio<Songs...>::template Rail>;

        template<template<auto...> class...Sequences>
        using SubRail = Trek<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Rail>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Rail>::template ProtoSail<Stockrooms...>;
    
        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Rail>::template ProtoZeal<Madness...>;
    
        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Rail>::template ProtoZest<Craziness...>;
    };
    
    template<template<template<template<auto...> class...> class...> class...Craziness>
    using Zest = ProtoZest<Craziness...>;
};

}}

#endif