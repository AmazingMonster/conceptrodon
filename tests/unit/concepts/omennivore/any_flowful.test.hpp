// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_FLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ANY_FLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/any_flowful.hpp"

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
namespace TestAnyFlowful {




/******************************************************************************************************/
static_assert(! AnyFlowful<Capsule<>, Capsule<int>, int>);

static_assert(! AnyFlowful<Shuttle<>, Shuttle<0>, int>);

static_assert(! AnyFlowful<Vehicle<>, Vehicle<Capsule>, int>);

static_assert(! AnyFlowful<Carrier<>, Carrier<Shuttle>, int>);

static_assert(AnyFlowful<Reverie<>, Reverie<Vehicle>, int>);

static_assert(! AnyFlowful<Phantom<>, Phantom<Carrier>, int>);

static_assert(! AnyFlowful<Forlorn<>, Forlorn<Reverie>, int>);

static_assert(! AnyFlowful<Travail<>, Travail<Phantom>, int>);

static_assert(! AnyFlowful<Lullaby<>, Lullaby<Forlorn>, int>);

static_assert(! AnyFlowful<Halcyon<>, Halcyon<Travail>, int>);

static_assert(! AnyFlowful<Pursuit<>, Pursuit<Lullaby>, int>);

static_assert(! AnyFlowful<Persist<>, Persist<Halcyon>, int>);

static_assert(! AnyFlowful<Sunrise<>, Sunrise<Pursuit>, int>);

static_assert(! AnyFlowful<Morning<>, Morning<Persist>, int>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Args>
struct Tester
{
    static constexpr int value {0};
};

template<typename...Args>
requires AnyFlowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {1};
};

template<typename...Args>
requires AllFlowful<Args...>
struct Tester<Args...>
{
    static constexpr int value {2};
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(Tester<int, double>::value == 0);
static_assert(Tester<Reverie<>, Reverie<Vehicle>, int>::value == 1);
static_assert(Tester<Reverie<>, Reverie<Vehicle>>::value == 2);
/******************************************************************************************************/




}}}}

#endif