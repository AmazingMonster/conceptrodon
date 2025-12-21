// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_DAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_DAWNFUL_H

#include "conceptrodon/omennivore/concepts/all_dawnful.hpp"

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
namespace TestAllDawnful {

static_assert(! AllDawnful<Capsule<>, Capsule<int>>);

static_assert(! AllDawnful<Shuttle<>, Shuttle<0>>);

static_assert(! AllDawnful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllDawnful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllDawnful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllDawnful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllDawnful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllDawnful<Travail<>, Travail<Phantom>>);

static_assert(! AllDawnful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllDawnful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllDawnful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllDawnful<Persist<>, Persist<Halcyon>>);

static_assert(! AllDawnful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllDawnful<Morning<>, Morning<Persist>>);

}}}}

#endif