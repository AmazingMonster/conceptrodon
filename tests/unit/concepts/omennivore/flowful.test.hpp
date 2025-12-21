// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWFUL_H

#include "conceptrodon/concepts/omennivore/flowful.hpp"

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