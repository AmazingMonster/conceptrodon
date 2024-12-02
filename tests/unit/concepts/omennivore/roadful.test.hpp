// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADFUL_H

#include "conceptrodon/descend/omennivore/concepts/roadful.hpp"

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
namespace TestRoadful {

static_assert(! Roadful<Capsule<>>);

static_assert(! Roadful<Shuttle<>>);

static_assert(Roadful<Vehicle<>>);

static_assert(! Roadful<Carrier<>>);

static_assert(! Roadful<Reverie<>>);

static_assert(! Roadful<Phantom<>>);

static_assert(! Roadful<Forlorn<>>);

static_assert(! Roadful<Travail<>>);

static_assert(! Roadful<Lullaby<>>);

static_assert(! Roadful<Halcyon<>>);

static_assert(! Roadful<Pursuit<>>);

static_assert(! Roadful<Persist<>>);

static_assert(! Roadful<Sunrise<>>);

static_assert(! Roadful<Morning<>>);

}}}}

#endif