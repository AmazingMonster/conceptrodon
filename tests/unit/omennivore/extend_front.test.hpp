// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_FRONT_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_FRONT_H

#include <concepts>
#include <tuple>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/extend_front.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestExtendFront {




/******************************************************************************************************/
template<typename...>
struct TesterA {};

template<auto...>
struct TesterB {};

template<template<typename...> class...>
struct TesterC {};

template<template<auto...> class...>
struct TesterD {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterA<int, int, double>

SAME_TYPE(ExtendFront<TesterA<double>>::Mold_t<int, int>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterB<0, 0, 1>

SAME_TYPE(ExtendFront<TesterB<1>>::Page_t<0, 0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterC<Capsule, Capsule, std::tuple>

SAME_TYPE(ExtendFront<TesterC<std::tuple>>::Road_t<Capsule, Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterD<Shuttle, Shuttle, std::index_sequence>

SAME_TYPE(ExtendFront<TesterD<std::index_sequence>>::Rail_t<Shuttle, Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif