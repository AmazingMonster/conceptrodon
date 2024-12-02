// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNWILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_UNWILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unwillful.hpp"

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
namespace TestAnyUnwillful {




/******************************************************************************************************/
static_assert(AnyUnwillful<Capsule<>, Capsule<int>, int>);

static_assert(AnyUnwillful<Shuttle<>, Shuttle<0>, int>);

static_assert(AnyUnwillful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(AnyUnwillful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyUnwillful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnyUnwillful<Phantom<>, Phantom<Carrier>, int>);

static_assert(AnyUnwillful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(AnyUnwillful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyUnwillful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyUnwillful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyUnwillful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(AnyUnwillful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyUnwillful<Persist<>, Persist<Halcyon>>);

static_assert(AnyUnwillful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyUnwillful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyUnwillful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllUnwillful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<Persist<>, Persist<Halcyon>>::value == 0);
static_assert(Tester<Persist<>, Persist<Halcyon>, int>::value == 1);
static_assert(Tester<int, double>::value == 2);
/******************************************************************************************************/




}}}}

#endif