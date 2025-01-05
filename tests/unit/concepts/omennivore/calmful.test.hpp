// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMFUL_H

#include "conceptrodon/omennivore/concepts/calmful.hpp"

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
namespace TestCalmful {

static_assert(! Calmful<Capsule<>>);

static_assert(! Calmful<Shuttle<>>);

static_assert(! Calmful<Vehicle<>>);

static_assert(! Calmful<Carrier<>>);

static_assert(! Calmful<Reverie<>>);

static_assert(! Calmful<Phantom<>>);

static_assert(! Calmful<Forlorn<>>);

static_assert(! Calmful<Travail<>>);

static_assert(! Calmful<Lullaby<>>);

static_assert(Calmful<Halcyon<>>);

static_assert(! Calmful<Pursuit<>>);

static_assert(! Calmful<Persist<>>);

static_assert(! Calmful<Sunrise<>>);

static_assert(! Calmful<Morning<>>);

}}}}

#endif