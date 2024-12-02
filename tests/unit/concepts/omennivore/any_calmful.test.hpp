// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_CALMFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_calmful.hpp"

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
namespace TestAnyCalmful {




/******************************************************************************************************/
static_assert(! AnyCalmful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyCalmful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyCalmful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyCalmful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyCalmful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyCalmful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyCalmful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyCalmful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyCalmful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(AnyCalmful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyCalmful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyCalmful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyCalmful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyCalmful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyCalmful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllCalmful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Halcyon<>, Halcyon<Travail>, int>::value == 1);
static_assert(Tester<Halcyon<>, Halcyon<Travail>>::value == 2);
/******************************************************************************************************/




}}}}

#endif