// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_RAY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_RAY_H

#include <type_traits>
#include "conceptrodon/utilities/ray.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestRay {




/******************************************************************************************************/
/**** Operations ****/
template<template<auto...> class...>
struct Stoc_0 {};

template<template<auto...> class...>
struct Stoc_1 {};

/**** fun ****/
constexpr bool fun(Ray<Stoc_0>) { return false; }

constexpr bool fun(Ray<Stoc_1>) { return true; }

/**** gun ****/
constexpr auto gun(Ray<Stoc_0>) -> std::false_type;

constexpr auto gun(Ray<Stoc_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Ray<Stoc_0>{}));
static_assert(fun(Ray<Stoc_1>{}));
static_assert(not decltype(gun(std::declval<Ray<Stoc_0>>()))::value);
static_assert(decltype(gun(std::declval<Ray<Stoc_1>>()))::value);
/******************************************************************************************************/




}}}

#endif