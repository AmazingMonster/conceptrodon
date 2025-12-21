// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNSAILFUL_H

#include "conceptrodon/concepts/omennivore/unsailful.hpp"

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