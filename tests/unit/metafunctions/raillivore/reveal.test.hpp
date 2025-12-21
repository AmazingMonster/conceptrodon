// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_UNIT_TESTS_TEST_REVEAL_H
#define CONCEPTRODON_RAILLIVORE_UNIT_TESTS_TEST_REVEAL_H

#include <concepts>

#include "conceptrodon/metafunctions/raillivore/reveal.hpp"
#include "conceptrodon/utilities/carrier.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestReveal {




/******************************************************************************************************/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

template<template<auto...> class...Args>
struct Operation
{ using type = Carrier<Args...>; };
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier<Seq_2, Seq_3, Seq_0, Seq_1>

SAME_TYPE(Reveal<Operation>::Rail<Seq_2, Seq_3, Seq_0, Seq_1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif