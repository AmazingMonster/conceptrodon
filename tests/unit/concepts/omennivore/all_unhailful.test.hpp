// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNHAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNHAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unhailful.hpp"

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
namespace TestAllUnhailful {

static_assert(AllUnhailful<Capsule<>, Capsule<int>>);

static_assert(AllUnhailful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnhailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnhailful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnhailful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnhailful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnhailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllUnhailful<Travail<>, Travail<Phantom>>);

static_assert(AllUnhailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnhailful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnhailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnhailful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnhailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnhailful<Morning<>, Morning<Persist>>);

}}}}

#endif