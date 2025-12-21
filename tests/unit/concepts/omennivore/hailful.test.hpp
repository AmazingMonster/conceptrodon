// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_HAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_HAILFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/hailful.hpp"

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
namespace TestHailful {

static_assert(! Hailful<Capsule<>>);

static_assert(! Hailful<Shuttle<>>);

static_assert(! Hailful<Vehicle<>>);

static_assert(! Hailful<Carrier<>>);

static_assert(! Hailful<Reverie<>>);

static_assert(! Hailful<Phantom<>>);

static_assert(! Hailful<Forlorn<>>);

static_assert(Hailful<Travail<>>);

static_assert(! Hailful<Lullaby<>>);

static_assert(! Hailful<Halcyon<>>);

static_assert(! Hailful<Pursuit<>>);

static_assert(! Hailful<Persist<>>);

static_assert(! Hailful<Sunrise<>>);

static_assert(! Hailful<Morning<>>);

}}}}

#endif