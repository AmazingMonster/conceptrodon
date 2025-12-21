// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_VAY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_VAY_H

#include <type_traits>
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestVay {




/******************************************************************************************************/
/**** fun ****/
constexpr bool fun(Vay<0>) { return false; }

constexpr bool fun(Vay<1>) { return true; }

/**** gun ****/
constexpr auto gun(Vay<0>) -> std::false_type;

constexpr auto gun(Vay<1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Vay<0>{}));
static_assert(fun(Vay<1>{}));
static_assert(not decltype(gun(std::declval<Vay<0>>()))::value);
static_assert(decltype(gun(std::declval<Vay<1>>()))::value);
/******************************************************************************************************/




}}}

#endif