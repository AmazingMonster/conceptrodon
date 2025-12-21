// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_SKIP_H
#define CONCEPTRODON_PAGELIVORE_SKIP_H

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/vehicle.hpp"
#include "conceptrodon/utilities/carrier.hpp"
#include "conceptrodon/utilities/reverie.hpp"
#include "conceptrodon/utilities/phantom.hpp"
#include "conceptrodon/utilities/forlorn.hpp"
#include "conceptrodon/utilities/travail.hpp"
#include "conceptrodon/utilities/lullaby.hpp"
#include "conceptrodon/utilities/halcyon.hpp"
#include "conceptrodon/utilities/pursuit.hpp"
#include "conceptrodon/utilities/persist.hpp"
#include "conceptrodon/utilities/sunrise.hpp"
#include "conceptrodon/utilities/morning.hpp"

#include "conceptrodon/omennivore/press.hpp"

namespace Conceptrodon {
namespace Pagelis {

template<template<auto...> class Operation, typename...Items>
struct LoadSkip
{
    struct Commit
    {
        template<auto...Variables>
        using Page = Omennivore::Press<Operation<Variables...>>::template Mold<Items...>;
    };

    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    template<template<typename...> class...Containers>
    using Road = LoadSkip<Operation, Items..., Vehicle<Containers...>>;

    template<template<auto...> class...Sequences>
    using Rail = LoadSkip<Operation, Items..., Carrier<Sequences...>>;

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = LoadSkip<Operation, Items..., Reverie<Warehouses...>>;

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = LoadSkip<Operation, Items..., Phantom<Stockrooms...>>;

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = LoadSkip<Operation, Items..., Forlorn<Sorrow...>>;

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = LoadSkip<Operation, Items..., Travail<Melancholy...>>;

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = LoadSkip<Operation, Items..., Lullaby<Silence...>>;

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = LoadSkip<Operation, Items..., Halcyon<Tranquil...>>;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    using Grit = LoadSkip<Operation, Items..., Pursuit<Consistency...>>;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    using Will = LoadSkip<Operation, Items..., Persist<Perseverance...>>;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using Glow = LoadSkip<Operation, Items..., Sunrise<Sunshines...>>;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using Dawn = LoadSkip<Operation, Items..., Morning<Sunshines...>>;
};

}

namespace Pagelivore {

template<template<auto...> class Operation>
struct Skip: public Pagelis::LoadSkip<Operation> {};

}}

#endif