// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITFUL_H

#include "conceptrodon/descend/omennivore/concepts/gritful.hpp"

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
namespace TestGritful {

static_assert(! Gritful<Capsule<>>);

static_assert(! Gritful<Shuttle<>>);

static_assert(! Gritful<Vehicle<>>);

static_assert(! Gritful<Carrier<>>);

static_assert(! Gritful<Reverie<>>);

static_assert(! Gritful<Phantom<>>);

static_assert(! Gritful<Forlorn<>>);

static_assert(! Gritful<Travail<>>);

static_assert(! Gritful<Lullaby<>>);

static_assert(! Gritful<Halcyon<>>);

static_assert(Gritful<Pursuit<>>);

static_assert(! Gritful<Persist<>>);

static_assert(! Gritful<Sunrise<>>);

static_assert(! Gritful<Morning<>>);

}}}}

#endif