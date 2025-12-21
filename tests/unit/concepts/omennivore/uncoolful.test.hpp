// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNCOOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNCOOLFUL_H

#include "conceptrodon/concepts/omennivore/uncoolful.hpp"

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