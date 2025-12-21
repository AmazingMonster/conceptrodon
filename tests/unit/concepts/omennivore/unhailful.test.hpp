// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNHAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNHAILFUL_H

#include "conceptrodon/omennivore/concepts/unhailful.hpp"

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