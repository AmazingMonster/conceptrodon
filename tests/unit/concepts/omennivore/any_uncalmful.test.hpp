// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNCALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNCALMFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_uncalmful.hpp"

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
namespace TestAnyUncalmful {




/******************************************************************************************************/
static_assert(AnyUncalmful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUncalmful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUncalmful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUncalmful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUncalmful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUncalmful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUncalmful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUncalmful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUncalmful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUncalmful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyUncalmful<Halcyon<>, Halcyon<Travail>>);

static_assert(AnyUncalmful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUncalmful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUncalmful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUncalmful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUncalmful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUncalmful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Halcyon<>, Halcyon<Travail>>::value == 0);
static_assert(Tester<Halcyon<>, Halcyon<Travail>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif