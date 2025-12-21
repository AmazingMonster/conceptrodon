// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNROADFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/unroadful.hpp"

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