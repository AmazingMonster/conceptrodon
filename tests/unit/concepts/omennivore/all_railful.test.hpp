// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_RAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_RAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"

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
namespace TestAllRailful {

static_assert(! AllRailful<Capsule<>, Capsule<int>>);

static_assert(! AllRailful<Shuttle<>, Shuttle<0>>);

static_assert(! AllRailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllRailful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllRailful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllRailful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllRailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllRailful<Travail<>, Travail<Phantom>>);

static_assert(! AllRailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllRailful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllRailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllRailful<Persist<>, Persist<Halcyon>>);

static_assert(! AllRailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllRailful<Morning<>, Morning<Persist>>);

}}}}

#endif