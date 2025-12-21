// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_FLY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_FLY_H

#include <type_traits>
#include "conceptrodon/utilities/fly.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestFly {




/******************************************************************************************************/
/**** Operations ****/
template<template<template<typename...> class...> class...>
struct Op_0 {};

template<template<template<typename...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Fly<Op_0>) { return false; }

constexpr bool fun(Fly<Op_1>) { return true; }

/**** gun ****/
constexpr auto gun(Fly<Op_0>) -> std::false_type;

constexpr auto gun(Fly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Fly<Op_0>{}));
static_assert(fun(Fly<Op_1>{}));
static_assert(not decltype(gun(std::declval<Fly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Fly<Op_1>>()))::value);
/******************************************************************************************************/




}}}

#endif