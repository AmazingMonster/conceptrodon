// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_WILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_WILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_willful.hpp"

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
namespace TestAnyWillful {




/******************************************************************************************************/
static_assert(! AnyWillful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyWillful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyWillful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyWillful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyWillful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyWillful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyWillful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyWillful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyWillful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyWillful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyWillful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyWillful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyWillful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyWillful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyWillful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllWillful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Persist<>, Persist<Halcyon>, int>::value == 1);
static_assert(Tester<Persist<>, Persist<Halcyon>>::value == 2);
/******************************************************************************************************/




}}}}

#endif