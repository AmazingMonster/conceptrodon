// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_PAGEFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_pageful.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAnyPageful {




/******************************************************************************************************/
static_assert(! AnyPageful<Capsule<>, Capsule<int>, int>);

static_assert(AnyPageful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyPageful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyPageful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyPageful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyPageful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyPageful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyPageful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyPageful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyPageful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyPageful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyPageful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyPageful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyPageful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyPageful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllPageful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Shuttle<>, Shuttle<0>, int>::value == 1);
static_assert(Tester<Shuttle<>, Shuttle<0>>::value == 2);
/******************************************************************************************************/




}}}}

#endif