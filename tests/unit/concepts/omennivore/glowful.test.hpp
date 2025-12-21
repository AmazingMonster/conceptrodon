// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWFUL_H

#include "conceptrodon/concepts/omennivore/glowful.hpp"

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