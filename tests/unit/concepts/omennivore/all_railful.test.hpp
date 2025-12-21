// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_RAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_RAILFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_railful.hpp"

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
namespace TestAllRailful {

static_assert(! AllRailful<Capsule<>, Capsule<int>>);

static_assert(! AllRailful<Shuttle<>, Shuttle<0>>);

static_assert(! AllRailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllRailful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllRailful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllRailful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllRailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllRailful<Travail<>, Travail<Phantom>>);

static_assert(! AllRailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllRailful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllRailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllRailful<Persist<>, Persist<Halcyon>>);

static_assert(! AllRailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllRailful<Morning<>, Morning<Persist>>);

}}}}

#endif