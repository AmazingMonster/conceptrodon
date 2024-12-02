// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNFLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNFLOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/unflowful.hpp"

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
namespace TestUnflowful {

static_assert(Unflowful<Capsule<>>);

static_assert(Unflowful<Shuttle<>>);

static_assert(Unflowful<Vehicle<>>);

static_assert(Unflowful<Carrier<>>);

static_assert(! Unflowful<Reverie<>>);

static_assert(Unflowful<Phantom<>>);

static_assert(Unflowful<Forlorn<>>);

static_assert(Unflowful<Travail<>>);

static_assert(Unflowful<Lullaby<>>);

static_assert(Unflowful<Halcyon<>>);

static_assert(Unflowful<Pursuit<>>);

static_assert(Unflowful<Persist<>>);

static_assert(Unflowful<Sunrise<>>);

static_assert(Unflowful<Morning<>>);

}}}}

#endif