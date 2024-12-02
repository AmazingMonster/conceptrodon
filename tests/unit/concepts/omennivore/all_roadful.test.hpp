// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_ROADFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"

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
namespace TestAllRoadful {

static_assert(! AllRoadful<Capsule<>, Capsule<int>>);

static_assert(! AllRoadful<Shuttle<>, Shuttle<0>>);

static_assert(AllRoadful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllRoadful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllRoadful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllRoadful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllRoadful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllRoadful<Travail<>, Travail<Phantom>>);

static_assert(! AllRoadful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllRoadful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllRoadful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllRoadful<Persist<>, Persist<Halcyon>>);

static_assert(! AllRoadful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllRoadful<Morning<>, Morning<Persist>>);

}}}}

#endif