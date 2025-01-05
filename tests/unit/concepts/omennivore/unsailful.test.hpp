// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSAILFUL_H

#include "conceptrodon/omennivore/concepts/unsailful.hpp"

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
namespace TestUnsailful {

static_assert(Unsailful<Capsule<>>);

static_assert(Unsailful<Shuttle<>>);

static_assert(Unsailful<Vehicle<>>);

static_assert(Unsailful<Carrier<>>);

static_assert(Unsailful<Reverie<>>);

static_assert(! Unsailful<Phantom<>>);

static_assert(Unsailful<Forlorn<>>);

static_assert(Unsailful<Travail<>>);

static_assert(Unsailful<Lullaby<>>);

static_assert(Unsailful<Halcyon<>>);

static_assert(Unsailful<Pursuit<>>);

static_assert(Unsailful<Persist<>>);

static_assert(Unsailful<Sunrise<>>);

static_assert(Unsailful<Morning<>>);

}}}}

#endif