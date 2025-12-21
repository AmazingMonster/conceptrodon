// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_SAY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_SAY_H

#include <type_traits>
#include "conceptrodon/utilities/say.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestSay {




/******************************************************************************************************/
/**** Operations ****/
template<template<template<auto...> class...> class...>
struct Op_0 {};

template<template<template<auto...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Say<Op_0>) { return false; }

constexpr bool fun(Say<Op_1>) { return true; }

/**** gun ****/
constexpr auto gun(Say<Op_0>) -> std::false_type;

constexpr auto gun(Say<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Say<Op_0>{}));
static_assert(fun(Say<Op_1>{}));
static_assert(not decltype(gun(std::declval<Say<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Say<Op_1>>()))::value);
/******************************************************************************************************/




}}}

#endif