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
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"

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
    struct ProtoFlow<Vehicle> { static constexpr bool value {true}; };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;

// Sail
    template<template<template<auto...> class...> class...>
    struct ProtoSail {};

    template<>
    struct ProtoSail<Carrier> { static constexpr bool value {true}; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;

// Snow
    template<template<template<template<typename...> class...> class...> class...>
    struct ProtoSnow {};

    template<>
    struct ProtoSnow<Reverie> { static constexpr bool value {true}; };

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;

// Hail
    template<template<template<template<auto...> class...> class...> class...>
    struct ProtoHail {};

    template<>
    struct ProtoHail<Phantom> { static constexpr bool value {true}; };

    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;

// Cool
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    struct ProtoCool {};

    template<>
    struct ProtoCool<Forlorn> { static constexpr bool value {true}; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;

// Calm
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    struct ProtoCalm {};

    template<>
    struct ProtoCalm<Travail> { static constexpr bool value {true}; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;

// Grit
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    struct ProtoGrit {};

    template<>
    struct ProtoGrit<Lullaby> { static constexpr bool value {true}; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = ProtoGrit<Agreements...>;

// Will
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    struct ProtoWill {};

    template<>
    struct ProtoWill<Halcyon> { static constexpr bool value {true}; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;

// Glow
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    struct ProtoGlow {};

    template<>
    struct ProtoGlow<Pursuit> { static constexpr bool value {true}; };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;

// Dawn
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    struct ProtoDawn {};

    template<>
    struct ProtoDawn<Persist> { static constexpr bool value {true}; };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Flip<Tester>::Mold<int>::Rail<>::value);
VALID(Flip<Tester>::Page<0>::Rail<>::value);
VALID(Flip<Tester>::Road<Capsule>::Rail<>::value);
VALID(Flip<Tester>::Rail<Shuttle>::Rail<>::value);
VALID(Flip<Tester>::Flow<Vehicle>::Rail<>::value);
VALID(Flip<Tester>::Sail<Carrier>::Rail<>::value);
VALID(Flip<Tester>::Snow<Reverie>::Rail<>::value);
VALID(Flip<Tester>::Hail<Phantom>::Rail<>::value);
VALID(Flip<Tester>::Cool<Forlorn>::Rail<>::value);
VALID(Flip<Tester>::Calm<Travail>::Rail<>::value);
VALID(Flip<Tester>::Grit<Lullaby>::Rail<>::value);
VALID(Flip<Tester>::Will<Halcyon>::Rail<>::value);
VALID(Flip<Tester>::Glow<Pursuit>::Rail<>::value);
VALID(Flip<Tester>::Dawn<Persist>::Rail<>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"

#endif