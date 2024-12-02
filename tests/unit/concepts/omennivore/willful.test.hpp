// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/willful.hpp"

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
namespace TestWillful {

static_assert(! Willful<Capsule<>>);

static_assert(! Willful<Shuttle<>>);

static_assert(! Willful<Vehicle<>>);

static_assert(! Willful<Carrier<>>);

static_assert(! Willful<Reverie<>>);

static_assert(! Willful<Phantom<>>);

static_assert(! Willful<Forlorn<>>);

static_assert(! Willful<Travail<>>);

static_assert(! Willful<Lullaby<>>);

static_assert(! Willful<Halcyon<>>);

static_assert(! Willful<Pursuit<>>);

static_assert(Willful<Persist<>>);

static_assert(! Willful<Sunrise<>>);

static_assert(! Willful<Morning<>>);

}}}}

#endif