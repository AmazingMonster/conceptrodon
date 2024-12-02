// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNROADFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unroadful.hpp"

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
namespace TestAnyUnroadful {




/******************************************************************************************************/
static_assert(AnyUnroadful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnroadful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnroadful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyUnroadful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AnyUnroadful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnroadful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnroadful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnroadful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnroadful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnroadful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnroadful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnroadful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnroadful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnroadful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnroadful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnroadful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnroadful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Vehicle<>, Vehicle<Capsule>>::value == 0);
static_assert(Tester<Vehicle<>, Vehicle<Capsule>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif