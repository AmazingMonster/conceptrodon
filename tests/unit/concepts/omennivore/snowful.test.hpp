// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/snowful.hpp"

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