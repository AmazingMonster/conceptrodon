// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILFUL_H

#include "conceptrodon/omennivore/concepts/railful.hpp"

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