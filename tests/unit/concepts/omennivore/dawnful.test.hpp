// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/dawnful.hpp"

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
namespace TestDawnful {

static_assert(! Dawnful<Capsule<>>);

static_assert(! Dawnful<Shuttle<>>);

static_assert(! Dawnful<Vehicle<>>);

static_assert(! Dawnful<Carrier<>>);

static_assert(! Dawnful<Reverie<>>);

static_assert(! Dawnful<Phantom<>>);

static_assert(! Dawnful<Forlorn<>>);

static_assert(! Dawnful<Travail<>>);

static_assert(! Dawnful<Lullaby<>>);

static_assert(! Dawnful<Halcyon<>>);

static_assert(! Dawnful<Pursuit<>>);

static_assert(! Dawnful<Persist<>>);

static_assert(! Dawnful<Sunrise<>>);

static_assert(Dawnful<Morning<>>);

}}}}

#endif