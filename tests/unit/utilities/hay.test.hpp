// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_HAY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_HAY_H

#include <type_traits>
#include "conceptrodon/utilities/hay.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestHay {




/******************************************************************************************************/
/**** Operations ****/
template<template<template<template<auto...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<auto...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Hay<Op_0>) { return false; }

constexpr bool fun(Hay<Op_1>) { return true; }

/**** gun ****/
constexpr auto gun(Hay<Op_0>) -> std::false_type;

constexpr auto gun(Hay<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Hay<Op_0>{}));
static_assert(fun(Hay<Op_1>{}));
static_assert(not decltype(gun(std::declval<Hay<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Hay<Op_1>>()))::value);
/******************************************************************************************************/




}}}

#endif