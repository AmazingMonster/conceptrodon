// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RAMBLE_H
#define CONCEPTRODON_MOULDIVORE_RAMBLE_H

#include "conceptrodon/descend/descend/omennivore/wind.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Radio>
struct Ramble
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<typename Radio<Songs...>::type>::template UniRoad<Car>;

        template<template<template<typename...> class...> class...Tunes>
        using Flow = Omennivore::Wind<Tunes<Mold>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<typename Radio<Songs...>::type>::template UniRail<Car>;

        template<template<template<typename...> class...> class...Tunes>
        using Flow = Omennivore::Wind<Tunes<Mold>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<typename Radio<Songs...>::type>::template UniFlow<Car>;

        template<template<template<typename...> class...> class...Tunes>
        using Flow = Omennivore::Wind<Tunes<Mold>...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<typename Radio<Songs...>::type>::template UniSail<Car>;


        template<template<template<typename...> class...> class...Tunes>
        using Flow = Omennivore::Wind<Tunes<Mold>...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif