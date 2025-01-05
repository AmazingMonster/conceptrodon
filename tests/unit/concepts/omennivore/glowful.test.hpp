// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWFUL_H

#include "conceptrodon/omennivore/concepts/glowful.hpp"

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
namespace TestGlowful {

static_assert(! Glowful<Capsule<>>);

static_assert(! Glowful<Shuttle<>>);

static_assert(! Glowful<Vehicle<>>);

static_assert(! Glowful<Carrier<>>);

static_assert(! Glowful<Reverie<>>);

static_assert(! Glowful<Phantom<>>);

static_assert(! Glowful<Forlorn<>>);

static_assert(! Glowful<Travail<>>);

static_assert(! Glowful<Lullaby<>>);

static_assert(! Glowful<Halcyon<>>);

static_assert(! Glowful<Pursuit<>>);

static_assert(! Glowful<Persist<>>);

static_assert(Glowful<Sunrise<>>);

static_assert(! Glowful<Morning<>>);

}}}}

#endif