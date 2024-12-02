// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_DAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_DAWNFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_dawnful.hpp"

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
namespace TestAnyDawnful {




/******************************************************************************************************/
static_assert(! AnyDawnful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyDawnful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyDawnful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyDawnful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyDawnful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyDawnful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyDawnful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyDawnful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyDawnful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyDawnful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyDawnful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyDawnful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyDawnful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(AnyDawnful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyDawnful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllDawnful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Morning<>, Morning<Persist>, int>::value == 1);
static_assert(Tester<Morning<>, Morning<Persist>>::value == 2);
/******************************************************************************************************/




}}}}

#endif