// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILFUL_H

#include "conceptrodon/omennivore/concepts/railful.hpp"

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
namespace TestRailful {

static_assert(! Railful<Capsule<>>);

static_assert(! Railful<Shuttle<>>);

static_assert(! Railful<Vehicle<>>);

static_assert(Railful<Carrier<>>);

static_assert(! Railful<Reverie<>>);

static_assert(! Railful<Phantom<>>);

static_assert(! Railful<Forlorn<>>);

static_assert(! Railful<Travail<>>);

static_assert(! Railful<Lullaby<>>);

static_assert(! Railful<Halcyon<>>);

static_assert(! Railful<Pursuit<>>);

static_assert(! Railful<Persist<>>);

static_assert(! Railful<Sunrise<>>);

static_assert(! Railful<Morning<>>);

}}}}

#endif