// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_COOLFUL_H

#include "conceptrodon/concepts/omennivore/coolful.hpp"

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