// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNHAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNHAILFUL_H

#include "conceptrodon/omennivore/concepts/unhailful.hpp"

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
namespace TestUnhailful {

static_assert(Unhailful<Capsule<>>);

static_assert(Unhailful<Shuttle<>>);

static_assert(Unhailful<Vehicle<>>);

static_assert(Unhailful<Carrier<>>);

static_assert(Unhailful<Reverie<>>);

static_assert(Unhailful<Phantom<>>);

static_assert(Unhailful<Forlorn<>>);

static_assert(! Unhailful<Travail<>>);

static_assert(Unhailful<Lullaby<>>);

static_assert(Unhailful<Halcyon<>>);

static_assert(Unhailful<Pursuit<>>);

static_assert(Unhailful<Persist<>>);

static_assert(Unhailful<Sunrise<>>);

static_assert(Unhailful<Morning<>>);

}}}}

#endif