// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_CALMFUL_H

#include "conceptrodon/concepts/omennivore/all_calmful.hpp"

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
namespace TestAllCalmful {

static_assert(! AllCalmful<Capsule<>, Capsule<int>>);

static_assert(! AllCalmful<Shuttle<>, Shuttle<0>>);

static_assert(! AllCalmful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllCalmful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllCalmful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllCalmful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllCalmful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllCalmful<Travail<>, Travail<Phantom>>);

static_assert(! AllCalmful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllCalmful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllCalmful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllCalmful<Persist<>, Persist<Halcyon>>);

static_assert(! AllCalmful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllCalmful<Morning<>, Morning<Persist>>);

}}}}

#endif