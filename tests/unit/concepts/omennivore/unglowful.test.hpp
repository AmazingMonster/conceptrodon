// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNGLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNGLOWFUL_H

#include "conceptrodon/concepts/omennivore/unglowful.hpp"

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
namespace TestUnglowful {

static_assert(Unglowful<Capsule<>>);

static_assert(Unglowful<Shuttle<>>);

static_assert(Unglowful<Vehicle<>>);

static_assert(Unglowful<Carrier<>>);

static_assert(Unglowful<Reverie<>>);

static_assert(Unglowful<Phantom<>>);

static_assert(Unglowful<Forlorn<>>);

static_assert(Unglowful<Travail<>>);

static_assert(Unglowful<Lullaby<>>);

static_assert(Unglowful<Halcyon<>>);

static_assert(Unglowful<Pursuit<>>);

static_assert(Unglowful<Persist<>>);

static_assert(! Unglowful<Sunrise<>>);

static_assert(Unglowful<Morning<>>);

}}}}

#endif