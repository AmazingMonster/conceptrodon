// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNPAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNPAGEFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unpageful.hpp"

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
namespace TestAnyUnpageful {




/******************************************************************************************************/
static_assert(AnyUnpageful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnpageful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyUnpageful<Shuttle<>, Shuttle<0>>);

static_assert(AnyUnpageful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnpageful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnpageful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnpageful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnpageful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnpageful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnpageful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnpageful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnpageful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnpageful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnpageful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnpageful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnpageful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnpageful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Shuttle<>, Shuttle<0>>::value == 0);
static_assert(Tester<Shuttle<>, Shuttle<0>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif