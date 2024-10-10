// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TREK_H
#define CONCEPTRODON_MOULDIVORE_TREK_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Radio>
struct Trek
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>>;

        template<template<typename...> class...Containers>
        using Road = Trek<Mold>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Mold>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Mold>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Mold>::template ProtoZeal<Madness...>;

        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Mold>::template ProtoZest<Craziness...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::value>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Mold>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Mold>::template ProtoZeal<Madness...>;

        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Mold>::template ProtoZest<Craziness...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::template Mold>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Mold>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Mold>::template ProtoZeal<Madness...>;

        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Mold>::template ProtoZest<Craziness...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::template Page>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Mold>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Mold>::template ProtoZeal<Madness...>;

        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Mold>::template ProtoZest<Craziness...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

    template<template<template<template<typename...> class...> class...> class Car>
    struct ProtoZeal
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::template Road>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<template<typename...> class...> class...> class...Madness>
    using Zeal = ProtoZeal<Madness...>;

    template<template<template<template<auto...> class...> class...> class Car>
    struct ProtoZest
    {
        template<typename...Songs>
        using Mold = Car<Radio<Songs...>::template Rail>;

        template<template<auto...> class...Sequences>
        using Rail = Trek<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trek<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trek<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trek<Mold>::template ProtoSail<Stockrooms...>;

        template<template<template<template<typename...> class...> class...> class...Madness>
        using Zeal = Trek<Mold>::template ProtoZeal<Madness...>;

        template<template<template<template<auto...> class...> class...> class...Craziness>
        using Zest = Trek<Mold>::template ProtoZest<Craziness...>;
    };

    template<template<template<template<auto...> class...> class...> class...Craziness>
    using Zest = ProtoZest<Craziness...>;
};

}}

#endif