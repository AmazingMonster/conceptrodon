// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_MEMORIZE_H
#define CONCEPTRODON_PAGELIVORE_MEMORIZE_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"

#include "conceptrodon/omennivore/flatten.hpp"

namespace Conceptrodon {
namespace Pagelis {


template<template<auto...> class Operation, typename...Items>
struct Preload
{
    template<auto...Variables>
    using Page = Omennivore::Flatten<Operation<Variables...>>::template Mold<Items...>;

    template<typename...Elements>
    using Mold = Preload<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using SubPage = Preload<Operation, Items..., Shuttle<Variables...>>;

    template<template<typename...> class...Containers>
    using Road = Preload<Operation, Items..., Vehicle<Containers...>>;

    template<template<auto...> class...Sequences>
    using Rail = Preload<Operation, Items..., Carrier<Sequences...>>;

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Preload<Operation, Items..., Reverie<Warehouses...>>;

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Preload<Operation, Items..., Phantom<Stockrooms...>>;

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = Preload<Operation, Items..., Forlorn<Sorrow...>>;

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = Preload<Operation, Items..., Travail<Melancholy...>>;

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = Preload<Operation, Items..., Lullaby<Silence...>>;

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = Preload<Operation, Items..., Halcyon<Tranquil...>>;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines>
    using Grit = Preload<Operation, Items..., Persist<Sunshines...>>;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines>
    using Will = Preload<Operation, Items..., Pursuit<Sunshines...>>;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using Glow = Preload<Operation, Items..., Sunrise<Sunshines...>>;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using Dawn = Preload<Operation, Items..., Morning<Sunshines...>>;
};
}

namespace Pagelivore {

template<template<auto...> class Operation>
struct Memorize: public Pagelis::Preload<Operation> {};

}}

#endif