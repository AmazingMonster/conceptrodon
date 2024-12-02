// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_SNOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_snowful.hpp"

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
namespace TestAnySnowful {




/******************************************************************************************************/
static_assert(! AnySnowful<Capsule<>, Capsule<int>, int>);

static_assert(! AnySnowful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnySnowful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnySnowful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnySnowful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnySnowful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnySnowful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnySnowful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnySnowful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnySnowful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnySnowful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnySnowful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnySnowful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnySnowful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnySnowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllSnowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Forlorn<>, Forlorn<Reverie>, int>::value == 1);
static_assert(Tester<Forlorn<>, Forlorn<Reverie>>::value == 2);
/******************************************************************************************************/




}}}}

#endif