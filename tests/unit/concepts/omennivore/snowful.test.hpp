// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWFUL_H

#include "conceptrodon/omennivore/concepts/snowful.hpp"

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
namespace TestSnowful {

static_assert(! Snowful<Capsule<>>);

static_assert(! Snowful<Shuttle<>>);

static_assert(! Snowful<Vehicle<>>);

static_assert(! Snowful<Carrier<>>);

static_assert(! Snowful<Reverie<>>);

static_assert(! Snowful<Phantom<>>);

static_assert(Snowful<Forlorn<>>);

static_assert(! Snowful<Travail<>>);

static_assert(! Snowful<Lullaby<>>);

static_assert(! Snowful<Halcyon<>>);

static_assert(! Snowful<Pursuit<>>);

static_assert(! Snowful<Persist<>>);

static_assert(! Snowful<Sunrise<>>);

static_assert(! Snowful<Morning<>>);

}}}}

#endif