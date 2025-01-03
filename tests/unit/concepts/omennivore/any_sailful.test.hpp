// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_SAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_SAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_sailful.hpp"

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
namespace TestAnySailful {




/******************************************************************************************************/
static_assert(! AnySailful<Capsule<>, Capsule<int>, int>);

static_assert(! AnySailful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnySailful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnySailful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnySailful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(AnySailful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnySailful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnySailful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnySailful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnySailful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnySailful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnySailful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnySailful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnySailful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnySailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllSailful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Phantom<>, Phantom<Carrier>, int>::value == 1);
static_assert(Tester<Phantom<>, Phantom<Carrier>>::value == 2);
/******************************************************************************************************/




}}}}

#endif