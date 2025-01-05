// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_COOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_COOLFUL_H

#include "conceptrodon/omennivore/concepts/coolful.hpp"

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
namespace TestCoolful {

static_assert(! Coolful<Capsule<>>);

static_assert(! Coolful<Shuttle<>>);

static_assert(! Coolful<Vehicle<>>);

static_assert(! Coolful<Carrier<>>);

static_assert(! Coolful<Reverie<>>);

static_assert(! Coolful<Phantom<>>);

static_assert(! Coolful<Forlorn<>>);

static_assert(! Coolful<Travail<>>);

static_assert(Coolful<Lullaby<>>);

static_assert(! Coolful<Halcyon<>>);

static_assert(! Coolful<Pursuit<>>);

static_assert(! Coolful<Persist<>>);

static_assert(! Coolful<Sunrise<>>);

static_assert(! Coolful<Morning<>>);

}}}}

#endif