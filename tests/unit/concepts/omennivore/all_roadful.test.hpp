// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_ROADFUL_H

#include "conceptrodon/concepts/omennivore/all_roadful.hpp"

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/vehicle.hpp"
#include "conceptrodon/utilities/carrier.hpp"
#include "conceptrodon/utilities/reverie.hpp"
#include "conceptrodon/utilities/phantom.hpp"
#include "conceptrodon/utilities/forlorn.hpp"
#include "conceptrodon/utilities/travail.hpp"
#include "conceptrodon/utilities/lullaby.hpp"
#include "conceptrodon/utilities/halcyon.hpp"
#include "conceptrodon/utilities/pursuit.hpp"
#include "conceptrodon/utilities/persist.hpp"
#include "conceptrodon/utilities/sunrise.hpp"
#include "conceptrodon/utilities/morning.hpp"

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