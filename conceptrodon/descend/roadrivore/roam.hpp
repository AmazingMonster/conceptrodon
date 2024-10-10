// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_ROAM_H
#define CONCEPTRODON_ROADRIVORE_ROAM_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Radio>
struct Roam
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniRoad<Car>;

        template<template<typename...> class...Containers>
        using SubRoad = Roam<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Roam<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Road>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniRail<Car>;

        template<template<typename...> class...Containers>
        using SubRoad = Roam<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Roam<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Road>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniFlow<Car>;

        template<template<typename...> class...Containers>
        using SubRoad = Roam<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Roam<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Road>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniSail<Car>;

        template<template<typename...> class...Containers>
        using SubRoad = Roam<Road>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Roam<Road>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Road>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Road>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif