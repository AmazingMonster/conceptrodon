// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_BACK_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_BACK_H

#include <concepts>
#include <tuple>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/extend_back.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestExtendBack {




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
    TesterA<double, int, int>

SAME_TYPE(ExtendBack<TesterA<double>>::Mold_t<int, int>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterB<1, 0, 0>

SAME_TYPE(ExtendBack<TesterB<1>>::Page_t<0, 0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterC<std::tuple, Capsule, Capsule>

SAME_TYPE(ExtendBack<TesterC<std::tuple>>::Road_t<Capsule, Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterD<std::index_sequence, Shuttle, Shuttle>

SAME_TYPE(ExtendBack<TesterD<std::index_sequence>>::Rail_t<Shuttle, Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif