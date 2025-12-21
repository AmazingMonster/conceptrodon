// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_SAILFUL_H

#include "conceptrodon/concepts/omennivore/all_sailful.hpp"

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
namespace TestAllSailful {

static_assert(! AllSailful<Capsule<>, Capsule<int>>);

static_assert(! AllSailful<Shuttle<>, Shuttle<0>>);

static_assert(! AllSailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllSailful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllSailful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllSailful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllSailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllSailful<Travail<>, Travail<Phantom>>);

static_assert(! AllSailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllSailful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllSailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllSailful<Persist<>, Persist<Halcyon>>);

static_assert(! AllSailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllSailful<Morning<>, Morning<Persist>>);

}}}}

#endif