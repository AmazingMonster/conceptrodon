// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWFUL_H

#include "conceptrodon/omennivore/concepts/flowful.hpp"

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
namespace TestFlowful {

static_assert(! Flowful<Capsule<>>);

static_assert(! Flowful<Shuttle<>>);

static_assert(! Flowful<Vehicle<>>);

static_assert(! Flowful<Carrier<>>);

static_assert(Flowful<Reverie<>>);

static_assert(! Flowful<Phantom<>>);

static_assert(! Flowful<Forlorn<>>);

static_assert(! Flowful<Travail<>>);

static_assert(! Flowful<Lullaby<>>);

static_assert(! Flowful<Halcyon<>>);

static_assert(! Flowful<Pursuit<>>);

static_assert(! Flowful<Persist<>>);

static_assert(! Flowful<Sunrise<>>);

static_assert(! Flowful<Morning<>>);

}}}}

#endif