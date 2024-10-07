// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SEND_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SEND_H

#include <concepts>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/send.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestSend {




/******************************************************************************************************/
template<typename, typename, typename>
struct TesterA {};

template<auto, auto, auto>
struct TesterB {};

template<template<typename...> class, template<typename...> class, template<typename...> class>
struct TesterC {};

template<template<auto...> class, template<auto...> class, template<auto...> class>
struct TesterD {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterA<int, int, int>

SAME_TYPE(Send<Capsule<int, int, int>>::UniRoad<TesterA>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterB<0, 0, 0>

SAME_TYPE(Send<Shuttle<0, 0, 0>>::UniRail<TesterB>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterC<Capsule, Capsule, Capsule>

SAME_TYPE(Send<Reverie<Capsule, Capsule, Capsule>>::UniFlow<TesterC>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterD<Shuttle, Shuttle, Shuttle>

SAME_TYPE(Send<Phantom<Shuttle, Shuttle, Shuttle>>::UniSail<TesterD>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif