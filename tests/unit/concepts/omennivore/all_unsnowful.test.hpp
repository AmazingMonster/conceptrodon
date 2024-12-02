// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNSNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNSNOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unsnowful.hpp"

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
namespace TestAllUnsnowful {

static_assert(AllUnsnowful<Capsule<>, Capsule<int>>);

static_assert(AllUnsnowful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnsnowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnsnowful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnsnowful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnsnowful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllUnsnowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnsnowful<Travail<>, Travail<Phantom>>);

static_assert(AllUnsnowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnsnowful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnsnowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnsnowful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnsnowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnsnowful<Morning<>, Morning<Persist>>);

}}}}

#endif