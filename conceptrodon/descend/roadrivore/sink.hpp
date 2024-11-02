// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_SINK_H
#define CONCEPTRODON_ROADRIVORE_SINK_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/morning.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/arcadia.hpp"
#include "conceptrodon/nirvana.hpp"

#include "conceptrodon/omennivore/press.hpp"

namespace Conceptrodon {
namespace Roadria {


template<template<template<typename...> class...> class Operation, typename...Items>
struct LoadSink
{
    struct Realm
    {
        template<template<typename...> class...Containers>
        using Road = Omennivore::Press<Operation<Containers...>>::template Mold<Items...>;
    };

    template<typename...Elements>
    using Mold = LoadSink<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSink<Operation, Items..., Shuttle<Variables...>>;

    template<template<typename...> class...Containers>
    using Road = LoadSink<Operation, Items..., Reverie<Containers...>>;

    template<template<auto...> class...Sequences>
    using Rail = LoadSink<Operation, Items..., Phantom<Sequences...>>;

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = LoadSink<Operation, Items..., Forlorn<Warehouses...>>;

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = LoadSink<Operation, Items..., Travail<Stockrooms...>>;

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = LoadSink<Operation, Items..., Lullaby<Sorrow...>>;

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = LoadSink<Operation, Items..., Halcyon<Melancholy...>>;

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Lull = LoadSink<Operation, Items..., Pursuit<Silence...>>;

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = LoadSink<Operation, Items..., Persist<Tranquil...>>;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines>
    using Grit = LoadSink<Operation, Items..., Morning<Sunshines...>>;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines>
    using Will = LoadSink<Operation, Items..., Sunrise<Sunshines...>>;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using Glow = LoadSink<Operation, Items..., Arcadia<Sunshines...>>;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using Dawn = LoadSink<Operation, Items..., Nirvana<Sunshines...>>;
};
}

namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct Sink: public Roadria::LoadSink<Operation> {};

}}

#endif