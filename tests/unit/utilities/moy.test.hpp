// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_MOY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_MOY_H

#include <type_traits>
#include "conceptrodon/utilities/moy.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestMoy {




/******************************************************************************************************/
/**** Operations ****/
template<typename...>
struct Con_0 {};

template<typename...>
struct Con_1 {};

/**** fun ****/
constexpr bool fun(Moy<Con_0>) { return false; }

constexpr bool fun(Moy<Con_1>) { return true; }

/**** gun ****/
constexpr auto gun(Moy<Con_0>) -> std::false_type;

constexpr auto gun(Moy<Con_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Moy<Con_0>{}));
static_assert(fun(Moy<Con_1>{}));
static_assert(not decltype(gun(std::declval<Moy<Con_0>>()))::value);
static_assert(decltype(gun(std::declval<Moy<Con_1>>()))::value);
/******************************************************************************************************/




}}}

#endif