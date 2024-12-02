// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNRAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNRAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unrailful.hpp"

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
namespace TestAnyUnrailful {




/******************************************************************************************************/
static_assert(AnyUnrailful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnrailful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnrailful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnrailful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyUnrailful<Carrier<>, Carrier<Shuttle>>);

static_assert(AnyUnrailful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnrailful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnrailful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnrailful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnrailful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnrailful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnrailful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnrailful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnrailful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnrailful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnrailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnrailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Carrier<>, Carrier<Shuttle>>::value == 0);
static_assert(Tester<Carrier<>, Carrier<Shuttle>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif