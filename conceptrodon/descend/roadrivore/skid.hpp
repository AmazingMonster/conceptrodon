// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_SKID_H
#define CONCEPTRODON_ROADRIVORE_SKID_H

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
struct LoadSkid
{
    template<template<typename...> class...Containers>
    using Road = Omennivore::Press<Operation<Containers...>>::template Mold<Items...>;

    template<typename...Elements>
    using Mold = LoadSkid<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSkid<Operation, Items..., Shuttle<Variables...>>;

    template<template<typename...> class...Containers>
    using R_ad = LoadSkid<Operation, Items..., Reverie<Containers...>>;

    template<template<auto...> class...Sequences>
    using Rail = LoadSkid<Operation, Items..., Phantom<Sequences...>>;

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = LoadSkid<Operation, Items..., Forlorn<Warehouses...>>;

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = LoadSkid<Operation, Items..., Travail<Stockrooms...>>;

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = LoadSkid<Operation, Items..., Lullaby<Sorrow...>>;

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = LoadSkid<Operation, Items..., Halcyon<Melancholy...>>;

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Lull = LoadSkid<Operation, Items..., Pursuit<Silence...>>;

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = LoadSkid<Operation, Items..., Persist<Tranquil...>>;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines>
    using Grit = LoadSkid<Operation, Items..., Morning<Sunshines...>>;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines>
    using Will = LoadSkid<Operation, Items..., Sunrise<Sunshines...>>;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using Glow = LoadSkid<Operation, Items..., Arcadia<Sunshines...>>;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using Dawn = LoadSkid<Operation, Items..., Nirvana<Sunshines...>>;
};
}

namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct Skid: public Roadria::LoadSkid<Operation> {};

}}

#endif