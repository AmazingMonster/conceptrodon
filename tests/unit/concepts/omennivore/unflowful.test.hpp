// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNFLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNFLOWFUL_H

#include "conceptrodon/omennivore/concepts/unflowful.hpp"

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