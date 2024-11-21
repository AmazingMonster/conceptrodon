// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_SHUTTLE_H
#define CONCEPTRODON_TESTS_UNIT_SHUTTLE_H

#include "conceptrodon/shuttle.hpp"
#include <concepts>
#include <cstddef>

namespace Conceptrodon {
namespace UnitTests {
namespace TestShuttle {




/******************************************************************************************************/
using MonoArk = Ark<0>;
using QuadArk = Ark<0, 1, 2, 3>;

template<size_t...I>
constexpr bool fun(std::index_sequence<I...>)
{return true;}

static_assert(fun(QuadArk{}));
/******************************************************************************************************/




/******************************************************************************************************/
constexpr bool gun(auto)
{return false;}

template<size_t...I>
constexpr bool gun(std::index_sequence<I...>)
{return true;}

static_assert(! gun(QuadArk {}));
static_assert(gun(static_cast<QuadArk::integer_sequence>(QuadArk{})));
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(MonoArk::first() == 0);
static_assert(QuadArk::first() == 0);
static_assert(QuadArk::second() == 1);
static_assert(QuadArk::third() == 2);
static_assert(QuadArk::fourth() == 3);
static_assert(std::same_as<decltype(QuadArk::first()), size_t>);
/******************************************************************************************************/




}}}

#endif