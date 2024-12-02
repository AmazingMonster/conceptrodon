// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_MOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_MOLDFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_moldful.hpp"

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
namespace TestAnyMoldful {




/******************************************************************************************************/
static_assert(AnyMoldful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyMoldful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyMoldful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyMoldful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyMoldful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyMoldful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyMoldful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyMoldful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyMoldful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyMoldful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyMoldful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyMoldful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyMoldful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyMoldful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyMoldful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllMoldful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Capsule<>, Capsule<int>, int>::value == 1);
static_assert(Tester<Capsule<>, Capsule<int>>::value == 2);
/******************************************************************************************************/




}}}}

#endif