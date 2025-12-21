// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/roadful.hpp"

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