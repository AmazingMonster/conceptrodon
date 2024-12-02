// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_MOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_MOLDFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"

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
namespace TestAllMoldful {

static_assert(AllMoldful<Capsule<>, Capsule<int>>);

static_assert(! AllMoldful<Shuttle<>, Shuttle<0>>);

static_assert(! AllMoldful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllMoldful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllMoldful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllMoldful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllMoldful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllMoldful<Travail<>, Travail<Phantom>>);

static_assert(! AllMoldful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllMoldful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllMoldful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllMoldful<Persist<>, Persist<Halcyon>>);

static_assert(! AllMoldful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllMoldful<Morning<>, Morning<Persist>>);

}}}}

#endif