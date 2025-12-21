// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ALL_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ALL_COOLFUL_H

#include "conceptrodon/concepts/omennivore/all_coolful.hpp"

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
namespace TestAllCoolful {

static_assert(! AllCoolful<Capsule<>, Capsule<int>>);

static_assert(! AllCoolful<Shuttle<>, Shuttle<0>>);

static_assert(! AllCoolful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllCoolful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllCoolful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllCoolful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllCoolful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllCoolful<Travail<>, Travail<Phantom>>);

static_assert(AllCoolful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllCoolful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllCoolful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllCoolful<Persist<>, Persist<Halcyon>>);

static_assert(! AllCoolful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllCoolful<Morning<>, Morning<Persist>>);

}}}}

#endif