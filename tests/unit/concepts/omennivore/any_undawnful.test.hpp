// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNDAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNDAWNFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_undawnful.hpp"

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
namespace TestAnyUndawnful {




/******************************************************************************************************/
static_assert(AnyUndawnful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUndawnful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUndawnful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUndawnful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUndawnful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUndawnful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUndawnful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUndawnful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUndawnful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUndawnful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUndawnful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUndawnful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUndawnful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUndawnful<Morning<>, Morning<Persist>, int>);

static_assert(! AnyUndawnful<Morning<>, Morning<Persist>>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUndawnful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUndawnful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Morning<>, Morning<Persist>>::value == 0);
static_assert(Tester<Morning<>, Morning<Persist>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif