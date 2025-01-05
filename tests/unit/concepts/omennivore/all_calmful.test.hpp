// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_CALMFUL_H

#include "conceptrodon/omennivore/concepts/all_calmful.hpp"

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
namespace TestAllCalmful {

static_assert(! AllCalmful<Capsule<>, Capsule<int>>);

static_assert(! AllCalmful<Shuttle<>, Shuttle<0>>);

static_assert(! AllCalmful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllCalmful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllCalmful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllCalmful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllCalmful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllCalmful<Travail<>, Travail<Phantom>>);

static_assert(! AllCalmful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllCalmful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllCalmful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllCalmful<Persist<>, Persist<Halcyon>>);

static_assert(! AllCalmful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllCalmful<Morning<>, Morning<Persist>>);

}}}}

#endif