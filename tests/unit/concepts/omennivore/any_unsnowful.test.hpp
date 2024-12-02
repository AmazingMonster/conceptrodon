// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNSNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNSNOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unsnowful.hpp"

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
namespace TestAnyUnsnowful {




/******************************************************************************************************/
static_assert(AnyUnsnowful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnsnowful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnsnowful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnsnowful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnsnowful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnsnowful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnsnowful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyUnsnowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AnyUnsnowful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnsnowful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnsnowful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnsnowful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnsnowful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnsnowful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnsnowful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnsnowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnsnowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Forlorn<>, Forlorn<Reverie>>::value == 0);
static_assert(Tester<Forlorn<>, Forlorn<Reverie>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif