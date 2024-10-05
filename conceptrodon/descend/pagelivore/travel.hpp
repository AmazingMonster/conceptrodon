// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TRAVEL_H
#define CONCEPTRODON_PAGELIVORE_TRAVEL_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Radio>
struct Travel
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniRoad<Car>;

        template<template<typename...> class...Containers>
        using Road = Travel<Page>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Travel<Page>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Travel<Page>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Travel<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniRail<Car>;

        template<template<auto...> class...Sequences>
        using Rail = Travel<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Travel<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Travel<Page>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Travel<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniFlow<Car>;

        template<template<auto...> class...Sequences>
        using Rail = Travel<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Travel<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Travel<Page>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Travel<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniSail<Car>;

        template<template<auto...> class...Sequences>
        using Rail = Travel<Page>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Travel<Page>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Travel<Page>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Travel<Page>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif