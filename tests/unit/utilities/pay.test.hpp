// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_PAY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_PAY_H

#include <type_traits>
#include "conceptrodon/utilities/pay.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestPay {




/******************************************************************************************************/
/**** Operations ****/
template<auto...>
struct Seq_0 {};

template<auto...>
struct Seq_1 {};

/**** fun ****/
constexpr bool fun(Pay<Seq_0>) { return false; }

constexpr bool fun(Pay<Seq_1>) { return true; }

/**** gun ****/
constexpr auto gun(Pay<Seq_0>) -> std::false_type;

constexpr auto gun(Pay<Seq_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Pay<Seq_0>{}));
static_assert(fun(Pay<Seq_1>{}));
static_assert(not decltype(gun(std::declval<Pay<Seq_0>>()))::value);
static_assert(decltype(gun(std::declval<Pay<Seq_1>>()))::value);
/******************************************************************************************************/




}}}

#endif