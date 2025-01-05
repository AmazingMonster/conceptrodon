// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_HAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_HAILFUL_H

#include "conceptrodon/omennivore/concepts/hailful.hpp"

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