// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSNOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/unsnowful.hpp"

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
namespace TestUnsnowful {

static_assert(Unsnowful<Capsule<>>);

static_assert(Unsnowful<Shuttle<>>);

static_assert(Unsnowful<Vehicle<>>);

static_assert(Unsnowful<Carrier<>>);

static_assert(Unsnowful<Reverie<>>);

static_assert(Unsnowful<Phantom<>>);

static_assert(! Unsnowful<Forlorn<>>);

static_assert(Unsnowful<Travail<>>);

static_assert(Unsnowful<Lullaby<>>);

static_assert(Unsnowful<Halcyon<>>);

static_assert(Unsnowful<Pursuit<>>);

static_assert(Unsnowful<Persist<>>);

static_assert(Unsnowful<Sunrise<>>);

static_assert(Unsnowful<Morning<>>);

}}}}

#endif