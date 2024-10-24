// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_RAMBLE_H
#define CONCEPTRODON_ROADRIVORE_RAMBLE_H

#include "conceptrodon/descend/descend/omennivore/wind.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Radio>
struct Ramble
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniRoad<Car>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniRail<Car>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniFlow<Car>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<typename Radio<Songs...>::type>::template UniSail<Car>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif