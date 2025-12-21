// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_ROY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_ROY_H

#include <type_traits>
#include "conceptrodon/utilities/roy.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestRoy {




/******************************************************************************************************/
/**** Operations ****/
template<template<typename...> class...>
struct Ware_0 {};

template<template<typename...> class...>
struct Ware_1 {};

/**** fun ****/
constexpr bool fun(Roy<Ware_0>) { return false; }

constexpr bool fun(Roy<Ware_1>) { return true; }

/**** gun ****/
constexpr auto gun(Roy<Ware_0>) -> std::false_type;

constexpr auto gun(Roy<Ware_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Roy<Ware_0>{}));
static_assert(fun(Roy<Ware_1>{}));
static_assert(not decltype(gun(std::declval<Roy<Ware_0>>()))::value);
static_assert(decltype(gun(std::declval<Roy<Ware_1>>()))::value);
/******************************************************************************************************/




}}}

#endif