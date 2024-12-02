// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNPAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNPAGEFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unpageful.hpp"

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
namespace TestAllUnpageful {

static_assert(AllUnpageful<Capsule<>, Capsule<int>>);

static_assert(! AllUnpageful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnpageful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnpageful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnpageful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnpageful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnpageful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnpageful<Travail<>, Travail<Phantom>>);

static_assert(AllUnpageful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnpageful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnpageful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnpageful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnpageful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnpageful<Morning<>, Morning<Persist>>);

}}}}

#endif