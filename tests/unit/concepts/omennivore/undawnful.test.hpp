// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNDAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNDAWNFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/undawnful.hpp"

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
namespace TestUndawnful {

static_assert(Undawnful<Capsule<>>);

static_assert(Undawnful<Shuttle<>>);

static_assert(Undawnful<Vehicle<>>);

static_assert(Undawnful<Carrier<>>);

static_assert(Undawnful<Reverie<>>);

static_assert(Undawnful<Phantom<>>);

static_assert(Undawnful<Forlorn<>>);

static_assert(Undawnful<Travail<>>);

static_assert(Undawnful<Lullaby<>>);

static_assert(Undawnful<Halcyon<>>);

static_assert(Undawnful<Pursuit<>>);

static_assert(Undawnful<Persist<>>);

static_assert(Undawnful<Sunrise<>>);

static_assert(! Undawnful<Morning<>>);

}}}}

#endif