// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNCOOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNCOOLFUL_H

#include "conceptrodon/omennivore/concepts/uncoolful.hpp"

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
namespace TestUncoolful {

static_assert(Uncoolful<Capsule<>>);

static_assert(Uncoolful<Shuttle<>>);

static_assert(Uncoolful<Vehicle<>>);

static_assert(Uncoolful<Carrier<>>);

static_assert(Uncoolful<Reverie<>>);

static_assert(Uncoolful<Phantom<>>);

static_assert(Uncoolful<Forlorn<>>);

static_assert(Uncoolful<Travail<>>);

static_assert(! Uncoolful<Lullaby<>>);

static_assert(Uncoolful<Halcyon<>>);

static_assert(Uncoolful<Pursuit<>>);

static_assert(Uncoolful<Persist<>>);

static_assert(Uncoolful<Sunrise<>>);

static_assert(Uncoolful<Morning<>>);

}}}}

#endif