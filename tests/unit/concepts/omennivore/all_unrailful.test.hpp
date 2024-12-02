// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNRAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNRAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unrailful.hpp"

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
namespace TestAllUnrailful {

static_assert(AllUnrailful<Capsule<>, Capsule<int>>);

static_assert(AllUnrailful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnrailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllUnrailful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnrailful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnrailful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnrailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnrailful<Travail<>, Travail<Phantom>>);

static_assert(AllUnrailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnrailful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnrailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnrailful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnrailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnrailful<Morning<>, Morning<Persist>>);

}}}}

#endif