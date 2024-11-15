// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_FLIP_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_FLIP_H

#include <utility>
#include "conceptrodon/raillivore/flip.hpp"
#include "macaron/judgmental/valid.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"

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
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestFlip {




/******************************************************************************************************/
template<template<auto...> class...>
struct Tester
{ 
// Mold
    template<typename...>
    struct ProtoMold {};

    template<>
    struct ProtoMold<int> { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

// Page
    template<auto...>
    struct ProtoPage {};

    template<>
    struct ProtoPage<0> { static constexpr bool value {true}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

// Road
    template<template<typename...> class...>
    struct ProtoRoad {};

    template<>
    struct ProtoRoad<Capsule> { static constexpr bool value {true}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

// Rail
    template<template<auto...> class...>
    struct ProtoRail {};

    template<>
    struct ProtoRail<Shuttle> { static constexpr bool value {true}; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

// Flow
    template<template<template<typename...> class...> class...>
    struct ProtoFlow {};

    template<>
    struct ProtoFlow<Reverie> { static constexpr bool value {true}; };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;

// Sail
    template<template<template<auto...> class...> class...>
    struct ProtoSail {};

    template<>
    struct ProtoSail<Phantom> { static constexpr bool value {true}; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;

// Snow
    template<template<template<template<typename...> class...> class...> class...>
    struct ProtoSnow {};

    template<>
    struct ProtoSnow<Forlorn> { static constexpr bool value {true}; };

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;

// Hail
    template<template<template<template<auto...> class...> class...> class...>
    struct ProtoHail {};

    template<>
    struct ProtoHail<Travail> { static constexpr bool value {true}; };

    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;

// Lull
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    struct ProtoLull {};

    template<>
    struct ProtoLull<Lullaby> { static constexpr bool value {true}; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Lull = ProtoLull<Agreements...>;

// Calm
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    struct ProtoCalm {};

    template<>
    struct ProtoCalm<Halcyon> { static constexpr bool value {true}; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;

// Grit
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    struct ProtoGrit {};

    template<>
    struct ProtoGrit<Pursuit> { static constexpr bool value {true}; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = ProtoGrit<Agreements...>;

// Will
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    struct ProtoWill {};

    template<>
    struct ProtoWill<Persist> { static constexpr bool value {true}; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;

// Glow
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    struct ProtoGlow {};

    template<>
    struct ProtoGlow<Sunrise> { static constexpr bool value {true}; };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;

// Dawn
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    struct ProtoDawn {};

    template<>
    struct ProtoDawn<Morning> { static constexpr bool value {true}; };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Flip<Tester>::Mold<int>::Rail<>::value);
VALID(Flip<Tester>::Page<0>::Rail<>::value);
VALID(Flip<Tester>::Road<Capsule>::Rail<>::value);
VALID(Flip<Tester>::Rail<Shuttle>::Rail<>::value);
VALID(Flip<Tester>::Flow<Reverie>::Rail<>::value);
VALID(Flip<Tester>::Sail<Phantom>::Rail<>::value);
VALID(Flip<Tester>::Snow<Forlorn>::Rail<>::value);
VALID(Flip<Tester>::Hail<Travail>::Rail<>::value);
VALID(Flip<Tester>::Lull<Lullaby>::Rail<>::value);
VALID(Flip<Tester>::Calm<Halcyon>::Rail<>::value);
VALID(Flip<Tester>::Grit<Pursuit>::Rail<>::value);
VALID(Flip<Tester>::Will<Persist>::Rail<>::value);
VALID(Flip<Tester>::Glow<Sunrise>::Rail<>::value);
VALID(Flip<Tester>::Dawn<Morning>::Rail<>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"

#endif