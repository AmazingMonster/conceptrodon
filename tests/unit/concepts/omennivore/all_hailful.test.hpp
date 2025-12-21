// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_HAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_HAILFUL_H

#include "conceptrodon/concepts/omennivore/all_hailful.hpp"

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
namespace TestAllHailful {

static_assert(! AllHailful<Capsule<>, Capsule<int>>);

static_assert(! AllHailful<Shuttle<>, Shuttle<0>>);

static_assert(! AllHailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllHailful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllHailful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllHailful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllHailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllHailful<Travail<>, Travail<Phantom>>);

static_assert(! AllHailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllHailful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllHailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllHailful<Persist<>, Persist<Halcyon>>);

static_assert(! AllHailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllHailful<Morning<>, Morning<Persist>>);

}}}}

#endif