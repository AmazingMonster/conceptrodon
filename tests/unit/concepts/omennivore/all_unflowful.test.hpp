// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNFLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNFLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unflowful.hpp"

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
namespace TestAllUnflowful {

static_assert(AllUnflowful<Capsule<>, Capsule<int>>);

static_assert(AllUnflowful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnflowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnflowful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllUnflowful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnflowful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnflowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnflowful<Travail<>, Travail<Phantom>>);

static_assert(AllUnflowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnflowful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnflowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnflowful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnflowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnflowful<Morning<>, Morning<Persist>>);

}}}}

#endif