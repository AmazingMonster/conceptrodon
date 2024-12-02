// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/sailful.hpp"

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
namespace TestSailful {

static_assert(! Sailful<Capsule<>>);

static_assert(! Sailful<Shuttle<>>);

static_assert(! Sailful<Vehicle<>>);

static_assert(! Sailful<Carrier<>>);

static_assert(! Sailful<Reverie<>>);

static_assert(Sailful<Phantom<>>);

static_assert(! Sailful<Forlorn<>>);

static_assert(! Sailful<Travail<>>);

static_assert(! Sailful<Lullaby<>>);

static_assert(! Sailful<Halcyon<>>);

static_assert(! Sailful<Pursuit<>>);

static_assert(! Sailful<Persist<>>);

static_assert(! Sailful<Sunrise<>>);

static_assert(! Sailful<Morning<>>);

}}}}

#endif