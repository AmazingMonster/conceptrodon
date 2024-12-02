// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_COOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_COOLFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_coolful.hpp"

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
namespace TestAllCoolful {

static_assert(! AllCoolful<Capsule<>, Capsule<int>>);

static_assert(! AllCoolful<Shuttle<>, Shuttle<0>>);

static_assert(! AllCoolful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllCoolful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllCoolful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllCoolful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllCoolful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllCoolful<Travail<>, Travail<Phantom>>);

static_assert(AllCoolful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllCoolful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllCoolful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllCoolful<Persist<>, Persist<Halcyon>>);

static_assert(! AllCoolful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllCoolful<Morning<>, Morning<Persist>>);

}}}}

#endif