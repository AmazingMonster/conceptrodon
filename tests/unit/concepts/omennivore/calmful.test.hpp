// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMFUL_H

#include "conceptrodon/concepts/omennivore/calmful.hpp"

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