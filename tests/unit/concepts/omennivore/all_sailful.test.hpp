// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_sailful.hpp"

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
namespace TestAllSailful {

static_assert(! AllSailful<Capsule<>, Capsule<int>>);

static_assert(! AllSailful<Shuttle<>, Shuttle<0>>);

static_assert(! AllSailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllSailful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllSailful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllSailful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllSailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllSailful<Travail<>, Travail<Phantom>>);

static_assert(! AllSailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllSailful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllSailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllSailful<Persist<>, Persist<Halcyon>>);

static_assert(! AllSailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllSailful<Morning<>, Morning<Persist>>);

}}}}

#endif