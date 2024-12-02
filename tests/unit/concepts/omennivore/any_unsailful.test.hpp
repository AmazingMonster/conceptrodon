// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNSAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNSAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unsailful.hpp"

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
namespace TestAnyUnsailful {




/******************************************************************************************************/
static_assert(AnyUnsailful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnsailful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnsailful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnsailful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnsailful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnsailful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyUnsailful<Phantom<>, Phantom<Carrier>>);

static_assert(AnyUnsailful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnsailful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnsailful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnsailful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnsailful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnsailful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnsailful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnsailful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnsailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnsailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Phantom<>, Phantom<Carrier>>::value == 0);
static_assert(Tester<Phantom<>, Phantom<Carrier>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif