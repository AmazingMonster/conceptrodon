// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_HAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_HAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_hailful.hpp"

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
namespace TestAnyHailful {




/******************************************************************************************************/
static_assert(! AnyHailful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyHailful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyHailful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyHailful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyHailful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyHailful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyHailful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyHailful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyHailful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyHailful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyHailful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyHailful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyHailful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyHailful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyHailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllHailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Travail<>, Travail<Phantom>, int>::value == 1);
static_assert(Tester<Travail<>, Travail<Phantom>>::value == 2);
/******************************************************************************************************/




}}}}

#endif