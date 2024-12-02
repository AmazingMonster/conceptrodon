// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNHAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNHAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unhailful.hpp"

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
namespace TestAnyUnhailful {




/******************************************************************************************************/
static_assert(AnyUnhailful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnhailful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnhailful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnhailful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnhailful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnhailful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnhailful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnhailful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyUnhailful<Travail<>, Travail<Phantom>>);

static_assert(AnyUnhailful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnhailful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnhailful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnhailful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnhailful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnhailful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnhailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnhailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Travail<>, Travail<Phantom>>::value == 0);
static_assert(Tester<Travail<>, Travail<Phantom>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif