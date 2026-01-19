// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_TYY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_TYY_H

#include <type_traits>
#include "conceptrodon/utilities/tyy.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestTyy {




/******************************************************************************************************/
/**** fun ****/
constexpr bool fun(Tyy<Vay<0>>) { return false; }

constexpr bool fun(Tyy<Vay<1>>) { return true; }

/**** gun ****/
constexpr auto gun(Tyy<Vay<0>>) -> std::false_type;

constexpr auto gun(Tyy<Vay<1>>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Tyy<Vay<0>>{}));
static_assert(fun(Tyy<Vay<1>>{}));
static_assert(not decltype(gun(std::declval<Tyy<Vay<0>>>()))::value);
static_assert(decltype(gun(std::declval<Tyy<Vay<1>>>()))::value);
/******************************************************************************************************/




}}}

#endif