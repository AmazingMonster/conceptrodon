// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNROADFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/unroadful.hpp"

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
namespace TestUnroadful {

static_assert(Unroadful<Capsule<>>);

static_assert(Unroadful<Shuttle<>>);

static_assert(! Unroadful<Vehicle<>>);

static_assert(Unroadful<Carrier<>>);

static_assert(Unroadful<Reverie<>>);

static_assert(Unroadful<Phantom<>>);

static_assert(Unroadful<Forlorn<>>);

static_assert(Unroadful<Travail<>>);

static_assert(Unroadful<Lullaby<>>);

static_assert(Unroadful<Halcyon<>>);

static_assert(Unroadful<Pursuit<>>);

static_assert(Unroadful<Persist<>>);

static_assert(Unroadful<Sunrise<>>);

static_assert(Unroadful<Morning<>>);

}}}}

#endif