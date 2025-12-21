// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SNOWFUL_H

#include "conceptrodon/concepts/omennivore/all_snowful.hpp"

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
namespace TestAllSnowful {

static_assert(! AllSnowful<Capsule<>, Capsule<int>>);

static_assert(! AllSnowful<Shuttle<>, Shuttle<0>>);

static_assert(! AllSnowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllSnowful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllSnowful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllSnowful<Phantom<>, Phantom<Carrier>>);

static_assert(AllSnowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllSnowful<Travail<>, Travail<Phantom>>);

static_assert(! AllSnowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllSnowful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllSnowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllSnowful<Persist<>, Persist<Halcyon>>);

static_assert(! AllSnowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllSnowful<Morning<>, Morning<Persist>>);

}}}}

#endif