// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_ROAM_H
#define CONCEPTRODON_RAILLIVORE_ROAM_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Radio>
struct Roam
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<auto...> class...Songs>
        using Rail = Omennivore::Send<typename Radio<Songs...>::type>::template UniRoad<Car>;

        template<template<auto...> class...Sequences>
        using SubRail = Roam<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Roam<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Rail>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Rail>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<auto...> class...Songs>
        using Rail = Omennivore::Send<typename Radio<Songs...>::type>::template UniRail<Car>;

        template<template<auto...> class...Sequences>
        using SubRail = Roam<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Roam<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Rail>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Rail>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<auto...> class...Songs>
        using Rail = Omennivore::Send<typename Radio<Songs...>::type>::template UniFlow<Car>;

        template<template<auto...> class...Sequences>
        using SubRail = Roam<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Roam<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Rail>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Rail>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<auto...> class...Songs>
        using Rail = Omennivore::Send<typename Radio<Songs...>::type>::template UniSail<Car>;

        template<template<auto...> class...Sequences>
        using SubRail = Roam<Rail>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Roam<Rail>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Roam<Rail>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Roam<Rail>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif