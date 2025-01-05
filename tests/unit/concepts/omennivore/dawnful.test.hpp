// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNFUL_H

#include "conceptrodon/omennivore/concepts/dawnful.hpp"

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
namespace TestDawnful {

static_assert(! Dawnful<Capsule<>>);

static_assert(! Dawnful<Shuttle<>>);

static_assert(! Dawnful<Vehicle<>>);

static_assert(! Dawnful<Carrier<>>);

static_assert(! Dawnful<Reverie<>>);

static_assert(! Dawnful<Phantom<>>);

static_assert(! Dawnful<Forlorn<>>);

static_assert(! Dawnful<Travail<>>);

static_assert(! Dawnful<Lullaby<>>);

static_assert(! Dawnful<Halcyon<>>);

static_assert(! Dawnful<Pursuit<>>);

static_assert(! Dawnful<Persist<>>);

static_assert(! Dawnful<Sunrise<>>);

static_assert(Dawnful<Morning<>>);

}}}}

#endif