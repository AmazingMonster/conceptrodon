// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNGRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNGRITFUL_H

#include "conceptrodon/omennivore/concepts/ungritful.hpp"

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
namespace TestUngritful {

static_assert(Ungritful<Capsule<>>);

static_assert(Ungritful<Shuttle<>>);

static_assert(Ungritful<Vehicle<>>);

static_assert(Ungritful<Carrier<>>);

static_assert(Ungritful<Reverie<>>);

static_assert(Ungritful<Phantom<>>);

static_assert(Ungritful<Forlorn<>>);

static_assert(Ungritful<Travail<>>);

static_assert(Ungritful<Lullaby<>>);

static_assert(Ungritful<Halcyon<>>);

static_assert(! Ungritful<Pursuit<>>);

static_assert(Ungritful<Persist<>>);

static_assert(Ungritful<Sunrise<>>);

static_assert(Ungritful<Morning<>>);

}}}}

#endif