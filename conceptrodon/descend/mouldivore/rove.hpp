// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ROVE_H
#define CONCEPTRODON_MOULDIVORE_ROVE_H

#include "conceptrodon/omennivore/send.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Radio>
struct Rove
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<Radio<Songs...>>::template UniRoad<Car>;

        template<template<typename...> class...Containers>
        using Road = Rove<Mold>::template ProtoRoad<Containers...>;

        template<template<auto...> class...Sequences>
        using Rail = Rove<Mold>::template ProtoRail<Sequences...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Rove<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Rove<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class Car>
    struct ProtoRail
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<Radio<Songs...>>::template UniRail<Car>;

        template<template<auto...> class...Sequences>
        using Rail = Rove<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Rove<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Rove<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Rove<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<Radio<Songs...>>::template UniFlow<Car>;

        template<template<auto...> class...Sequences>
        using Rail = Rove<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Rove<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Rove<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Rove<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        template<typename...Songs>
        using Mold = Omennivore::Send<Radio<Songs...>>::template UniSail<Car>;

        template<template<auto...> class...Sequences>
        using Rail = Rove<Mold>::template ProtoRail<Sequences...>;

        template<template<typename...> class...Containers>
        using Road = Rove<Mold>::template ProtoRoad<Containers...>;

        template<template<template<typename...> class...> class...Warehouses>
        using Flow = Rove<Mold>::template ProtoFlow<Warehouses...>;

        template<template<template<auto...> class...> class...Stockrooms>
        using Sail = Rove<Mold>::template ProtoSail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif