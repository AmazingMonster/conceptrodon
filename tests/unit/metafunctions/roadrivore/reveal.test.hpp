// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_REVEAL_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_REVEAL_H

#include <concepts>

#include "conceptrodon/roadrivore/reveal.hpp"
#include "conceptrodon/vehicle.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestReveal {




/******************************************************************************************************/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<template<typename...> class...Args>
struct Operation
{ using type = Vehicle<Args...>; };
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Vehicle<Con_2, Con_3, Con_0, Con_1>

SAME_TYPE(Reveal<Operation>::Road<Con_2, Con_3, Con_0, Con_1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif