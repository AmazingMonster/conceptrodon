// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SNOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_snowful.hpp"

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
namespace TestAllSnowful {

static_assert(! AllSnowful<Capsule<>, Capsule<int>>);

static_assert(! AllSnowful<Shuttle<>, Shuttle<0>>);

static_assert(! AllSnowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllSnowful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllSnowful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllSnowful<Phantom<>, Phantom<Carrier>>);

static_assert(AllSnowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllSnowful<Travail<>, Travail<Phantom>>);

static_assert(! AllSnowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllSnowful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllSnowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllSnowful<Persist<>, Persist<Halcyon>>);

static_assert(! AllSnowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllSnowful<Morning<>, Morning<Persist>>);

}}}}

#endif