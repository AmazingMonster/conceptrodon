// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/willful.hpp"

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
namespace TestWillful {

static_assert(! Willful<Capsule<>>);

static_assert(! Willful<Shuttle<>>);

static_assert(! Willful<Vehicle<>>);

static_assert(! Willful<Carrier<>>);

static_assert(! Willful<Reverie<>>);

static_assert(! Willful<Phantom<>>);

static_assert(! Willful<Forlorn<>>);

static_assert(! Willful<Travail<>>);

static_assert(! Willful<Lullaby<>>);

static_assert(! Willful<Halcyon<>>);

static_assert(! Willful<Pursuit<>>);

static_assert(Willful<Persist<>>);

static_assert(! Willful<Sunrise<>>);

static_assert(! Willful<Morning<>>);

}}}}

#endif