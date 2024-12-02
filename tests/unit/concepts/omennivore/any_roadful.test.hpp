// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_ROADFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_roadful.hpp"

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
namespace TestAnyRoadful {




/******************************************************************************************************/
static_assert(! AnyRoadful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyRoadful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyRoadful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyRoadful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyRoadful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyRoadful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyRoadful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyRoadful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyRoadful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyRoadful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyRoadful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyRoadful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyRoadful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyRoadful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyRoadful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllRoadful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Vehicle<>, Vehicle<Capsule>, int>::value == 1);
static_assert(Tester<Vehicle<>, Vehicle<Capsule>>::value == 2);
/******************************************************************************************************/




}}}}

#endif