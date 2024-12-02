// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNGRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNGRITFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_ungritful.hpp"

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
namespace TestAnyUngritful {




/******************************************************************************************************/
static_assert(AnyUngritful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUngritful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUngritful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUngritful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUngritful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUngritful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUngritful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUngritful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUngritful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUngritful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUngritful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyUngritful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AnyUngritful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUngritful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUngritful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUngritful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUngritful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Pursuit<>, Pursuit<Lullaby>>::value == 0);
static_assert(Tester<Pursuit<>, Pursuit<Lullaby>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif