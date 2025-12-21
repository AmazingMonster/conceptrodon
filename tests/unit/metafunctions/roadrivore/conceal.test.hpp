// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_UNIT_TESTS_TEST_CONCEAL_H
#define CONCEPTRODON_ROADRIVORE_UNIT_TESTS_TEST_CONCEAL_H

#include <concepts>

#include "conceptrodon/metafunctions/roadrivore/conceal.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestConceal {




/******************************************************************************************************/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<template<typename...> class...>
struct Operation;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation<Con_2, Con_3, Con_0, Con_1>

SAME_TYPE(Conceal<Operation>::Road<Con_2, Con_3, Con_0, Con_1>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif