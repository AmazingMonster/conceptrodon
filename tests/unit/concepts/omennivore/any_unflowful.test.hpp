// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNFLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNFLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unflowful.hpp"

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
namespace TestAnyUnflowful {




/******************************************************************************************************/
static_assert(AnyUnflowful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnflowful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnflowful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnflowful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnflowful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyUnflowful<Reverie<>, Reverie<Vehicle>>);

static_assert(AnyUnflowful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnflowful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnflowful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnflowful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnflowful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnflowful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnflowful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnflowful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnflowful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnflowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnflowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Reverie<>, Reverie<Vehicle>>::value == 0);
static_assert(Tester<Reverie<>, Reverie<Vehicle>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif