// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNRAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNRAILFUL_H

#include "conceptrodon/omennivore/concepts/unrailful.hpp"

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
namespace TestUnrailful {

static_assert(Unrailful<Capsule<>>);

static_assert(Unrailful<Shuttle<>>);

static_assert(Unrailful<Vehicle<>>);

static_assert(! Unrailful<Carrier<>>);

static_assert(Unrailful<Reverie<>>);

static_assert(Unrailful<Phantom<>>);

static_assert(Unrailful<Forlorn<>>);

static_assert(Unrailful<Travail<>>);

static_assert(Unrailful<Lullaby<>>);

static_assert(Unrailful<Halcyon<>>);

static_assert(Unrailful<Pursuit<>>);

static_assert(Unrailful<Persist<>>);

static_assert(Unrailful<Sunrise<>>);

static_assert(Unrailful<Morning<>>);

}}}}

#endif