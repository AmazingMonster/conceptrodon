// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_RAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_RAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_railful.hpp"

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
namespace TestAnyRailful {




/******************************************************************************************************/
static_assert(! AnyRailful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyRailful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyRailful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyRailful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyRailful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyRailful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyRailful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyRailful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyRailful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyRailful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyRailful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyRailful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyRailful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyRailful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyRailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllRailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Carrier<>, Carrier<Shuttle>, int>::value == 1);
static_assert(Tester<Carrier<>, Carrier<Shuttle>>::value == 2);
/******************************************************************************************************/




}}}}

#endif