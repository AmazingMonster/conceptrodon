// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RAMBLE_H
#define CONCEPTRODON_PAGELIVORE_RAMBLE_H

#include "conceptrodon/descend/descend/omennivore/wind.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Radio>
struct Ramble
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniRoad<Car>;

        template<template<template<auto...> class...> class...Tunes>
        using Sail = Omennivore::Wind<Tunes<Page>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniRail<Car>;

        template<template<template<auto...> class...> class...Tunes>
        using Sail = Omennivore::Wind<Tunes<Page>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniFlow<Car>;

        template<template<template<auto...> class...> class...Tunes>
        using Sail = Omennivore::Wind<Tunes<Page>...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<auto...Songs>
        using Page = Omennivore::Send<typename Radio<Songs...>::type>::template UniSail<Car>;

        template<template<template<auto...> class...> class...Tunes>
        using Sail = Omennivore::Wind<Tunes<Page>...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif