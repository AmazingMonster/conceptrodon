// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_LORE_H
#define CONCEPTRODON_MOULDIVORE_LORE_H

#include "conceptrodon/descend/descend/omennivore/wind.hpp"
#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Car>
struct Lore
{
    template<template<typename...> class Radio>
    struct ProtoRoad
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<Radio<Songs...>>::template UniRoad<Car>;

        template<template<template<typename...> class...> class...Memories>
        using Flow = Omennivore::Wind<Memories<Mold>...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Radio>
    struct ProtoRail
    {
        template<auto...Songs>
        using Page = Omennivore::Send<Radio<Songs...>>::template UniRoad<Car>;

        template<template<template<auto...> class...> class...Memories>
        using Sail = Omennivore::Wind<Memories<Page>...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Radio>
    struct ProtoFlow
    {
        template<template<typename...> class...Songs>
        using Road = Omennivore::Send<Radio<Songs...>>::template UniRoad<Car>;

        template<template<template<template<typename...> class...> class...> class...Memories>
        using Zeal = Omennivore::Wind<Memories<Road>...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Radio>
    struct ProtoSail
    {
        template<template<auto...> class...Songs>
        using Rail = Omennivore::Send<Radio<Songs...>>::template UniRoad<Car>;

        template<template<template<template<auto...> class...> class...> class...Memories>
        using Zest = Omennivore::Wind<Memories<Rail>...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif