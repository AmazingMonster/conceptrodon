// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_FLIP_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_FLIP_H

#include <utility>
#include "conceptrodon/mouldivore/flip.hpp"
#include "macaron/judgmental/valid.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestFlip {




/******************************************************************************************************/
template<typename...>
struct Tester
{ 
    template<typename...>
    struct ProtoMold {};

    template<>
    struct ProtoMold<int> { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<auto...>
    struct ProtoPage {};

    template<>
    struct ProtoPage<0> { static constexpr bool value {true}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<template<typename...> class...>
    struct ProtoRoad {};

    template<>
    struct ProtoRoad<std::tuple> { static constexpr bool value {true}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<auto...> class...>
    struct ProtoRail {};

    template<>
    struct ProtoRail<std::index_sequence> { static constexpr bool value {true}; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<template<typename...> class...> class...>
    struct ProtoFlow {};

    template<>
    struct ProtoFlow<Reverie> { static constexpr bool value {true}; };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;

    template<template<template<auto...> class...> class...>
    struct ProtoSail {};

    template<>
    struct ProtoSail<Phantom> { static constexpr bool value {true}; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Flip<Tester>::Mold<int>::Mold<>::value);
VALID(Flip<Tester>::Page<0>::Mold<>::value);
VALID(Flip<Tester>::Road<std::tuple>::Mold<>::value);
VALID(Flip<Tester>::Rail<std::index_sequence>::Mold<>::value);
VALID(Flip<Tester>::Flow<Reverie>::Mold<>::value);
VALID(Flip<Tester>::Sail<Phantom>::Mold<>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"

#endif