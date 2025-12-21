// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNRAILFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNRAILFUL_H

#include "conceptrodon/concepts/omennivore/unrailful.hpp"

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