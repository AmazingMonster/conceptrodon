// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNGLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNGLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unglowful.hpp"

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
namespace TestAllUnglowful {

static_assert(AllUnglowful<Capsule<>, Capsule<int>>);

static_assert(AllUnglowful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnglowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnglowful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnglowful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnglowful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnglowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnglowful<Travail<>, Travail<Phantom>>);

static_assert(AllUnglowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnglowful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnglowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnglowful<Persist<>, Persist<Halcyon>>);

static_assert(! AllUnglowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnglowful<Morning<>, Morning<Persist>>);

}}}}

#endif