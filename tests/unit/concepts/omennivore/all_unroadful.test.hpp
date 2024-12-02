// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNROADFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unroadful.hpp"

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
namespace TestAllUnroadful {

static_assert(AllUnroadful<Capsule<>, Capsule<int>>);

static_assert(AllUnroadful<Shuttle<>, Shuttle<0>>);

static_assert(! AllUnroadful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnroadful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnroadful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnroadful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnroadful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnroadful<Travail<>, Travail<Phantom>>);

static_assert(AllUnroadful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnroadful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnroadful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnroadful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnroadful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnroadful<Morning<>, Morning<Persist>>);

}}}}

#endif