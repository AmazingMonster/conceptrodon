// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_GLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_GLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_glowful.hpp"

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
namespace TestAnyGlowful {




/******************************************************************************************************/
static_assert(! AnyGlowful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyGlowful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyGlowful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyGlowful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(! AnyGlowful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyGlowful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyGlowful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyGlowful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyGlowful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyGlowful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyGlowful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyGlowful<Persist<>, Persist<Halcyon>, int>);

static_assert(AnyGlowful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyGlowful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyGlowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllGlowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Sunrise<>, Sunrise<Pursuit>, int>::value == 1);
static_assert(Tester<Sunrise<>, Sunrise<Pursuit>>::value == 2);
/******************************************************************************************************/




}}}}

#endif