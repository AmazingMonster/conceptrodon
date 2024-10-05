// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TRIP_H
#define CONCEPTRODON_PAGELIVORE_TRIP_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Radio>
struct Trip
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<auto...Songs>
        using Page = Car<typename Radio<Songs...>::type>;

        template<template<typename...> class...Containers>
        using Road = Trip<Page>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Page>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::value>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trip<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::template Mold>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trip<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<auto...Songs>
        using Page = Car<Radio<Songs...>::template Page>;

        template<template<auto...> class...Sequences>
        using Rail = Trip<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Trip<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Trip<Page>::template ProtoFlow<Warehouses...>;
    
        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Trip<Page>::template ProtoSail<Stockrooms...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif