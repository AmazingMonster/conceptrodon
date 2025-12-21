// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSNOWFUL_H

#include "conceptrodon/omennivore/concepts/unsnowful.hpp"

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