// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SAILFUL_H

#include "conceptrodon/omennivore/concepts/sailful.hpp"

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