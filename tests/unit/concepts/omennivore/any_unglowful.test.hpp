// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNGLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNGLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unglowful.hpp"

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
namespace TestAnyUnglowful {




/******************************************************************************************************/
static_assert(AnyUnglowful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnglowful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnglowful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnglowful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnglowful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnglowful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnglowful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnglowful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnglowful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnglowful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnglowful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnglowful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnglowful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyUnglowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AnyUnglowful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnglowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnglowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Sunrise<>, Sunrise<Pursuit>>::value == 0);
static_assert(Tester<Sunrise<>, Sunrise<Pursuit>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif