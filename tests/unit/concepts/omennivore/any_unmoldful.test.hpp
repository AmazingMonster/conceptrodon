// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNMOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNMOLDFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unmoldful.hpp"

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
namespace TestAnyUnmoldful {




/******************************************************************************************************/
static_assert(! AnyUnmoldful<Capsule<>, Capsule<int>>);

static_assert(AnyUnmoldful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnmoldful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnmoldful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnmoldful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnmoldful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnmoldful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnmoldful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnmoldful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnmoldful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnmoldful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnmoldful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnmoldful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyUnmoldful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnmoldful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnmoldful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnmoldful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Capsule<>, Capsule<int>>::value == 0);
static_assert(Tester<Capsule<>, Capsule<int>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif