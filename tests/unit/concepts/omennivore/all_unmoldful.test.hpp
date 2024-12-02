// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNMOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNMOLDFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unmoldful.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllUnmoldful {

static_assert(! AllUnmoldful<Capsule<>, Capsule<int>>);

static_assert(AllUnmoldful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnmoldful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnmoldful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnmoldful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnmoldful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnmoldful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnmoldful<Travail<>, Travail<Phantom>>);

static_assert(AllUnmoldful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnmoldful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnmoldful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnmoldful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnmoldful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnmoldful<Morning<>, Morning<Persist>>);

}}}}

#endif