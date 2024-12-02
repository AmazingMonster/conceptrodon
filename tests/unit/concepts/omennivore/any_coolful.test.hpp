// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_COOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_COOLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_coolful.hpp"

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
namespace TestAnyCoolful {




/******************************************************************************************************/
static_assert(! AnyCoolful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyCoolful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyCoolful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyCoolful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyCoolful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyCoolful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyCoolful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyCoolful<Travail<>, Travail<Phantom>, int>);

static_assert(AnyCoolful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyCoolful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyCoolful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyCoolful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyCoolful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyCoolful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyCoolful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllCoolful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Lullaby<>, Lullaby<Forlorn>, int>::value == 1);
static_assert(Tester<Lullaby<>, Lullaby<Forlorn>>::value == 2);
/******************************************************************************************************/




}}}}

#endif