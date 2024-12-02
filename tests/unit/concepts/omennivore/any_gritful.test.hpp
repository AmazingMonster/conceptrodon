// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_GRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_GRITFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_gritful.hpp"

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
namespace TestAnyGritful {




/******************************************************************************************************/
static_assert(! AnyGritful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyGritful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyGritful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyGritful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyGritful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyGritful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyGritful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyGritful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyGritful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyGritful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(AnyGritful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyGritful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyGritful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyGritful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyGritful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllGritful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Pursuit<>, Pursuit<Lullaby>, int>::value == 1);
static_assert(Tester<Pursuit<>, Pursuit<Lullaby>>::value == 2);
/******************************************************************************************************/




}}}}

#endif