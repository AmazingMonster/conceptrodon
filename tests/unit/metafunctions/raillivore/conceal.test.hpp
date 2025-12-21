// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_CONCEAL_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_CONCEAL_H

#include <concepts>

#include "conceptrodon/metafunctions/raillivore/conceal.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestConceal {




/******************************************************************************************************/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

template<template<auto...> class...>
struct Operation;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation<Seq_2, Seq_3, Seq_0, Seq_1>

SAME_TYPE(Conceal<Operation>::Rail<Seq_2, Seq_3, Seq_0, Seq_1>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif