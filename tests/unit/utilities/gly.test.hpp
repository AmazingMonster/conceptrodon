// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_GLY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_GLY_H

#include <type_traits>
#include "conceptrodon/utilities/gly.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestGly {




/******************************************************************************************************/
/**** Operations ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Gly<Op_0>) { return false; }

constexpr bool fun(Gly<Op_1>) { return true; }

/**** gun ****/
constexpr auto gun(Gly<Op_0>) -> std::false_type;

constexpr auto gun(Gly<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not fun(Gly<Op_0>{}));
static_assert(fun(Gly<Op_1>{}));
static_assert(not decltype(gun(std::declval<Gly<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Gly<Op_1>>()))::value);
/******************************************************************************************************/




}}}

#endif