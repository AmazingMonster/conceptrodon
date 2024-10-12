// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_VOYAGE_H
#define CONCEPTRODON_ROADRIVORE_VOYAGE_H

#include "conceptrodon/descend/descend/omennivore/wind.hpp"

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Radio>
struct Voyage
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::value>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<template<typename...> class...Songs>
        using Road = Car<Radio<Songs...>::template Mold>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<template<typename...> class...Songs>
        using Road= Car<Radio<Songs...>::template Page>;

        template<template<template<template<typename...> class...> class...> class...Tunes>
        using Snow = Omennivore::Wind<Tunes<Road>...>;
    };
    
    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif