// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNCOOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNCOOLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_uncoolful.hpp"

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
namespace TestAnyUncoolful {




/******************************************************************************************************/
static_assert(AnyUncoolful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUncoolful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUncoolful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUncoolful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUncoolful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUncoolful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUncoolful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUncoolful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUncoolful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyUncoolful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AnyUncoolful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUncoolful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUncoolful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUncoolful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUncoolful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUncoolful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUncoolful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Lullaby<>, Lullaby<Forlorn>>::value == 0);
static_assert(Tester<Lullaby<>, Lullaby<Forlorn>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif