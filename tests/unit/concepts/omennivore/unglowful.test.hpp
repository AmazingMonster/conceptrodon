// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNGLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNGLOWFUL_H

#include "conceptrodon/omennivore/concepts/unglowful.hpp"

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