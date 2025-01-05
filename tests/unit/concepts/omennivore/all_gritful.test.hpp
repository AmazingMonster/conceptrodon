// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_GRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_GRITFUL_H

#include "conceptrodon/omennivore/concepts/all_gritful.hpp"

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
namespace TestAllGritful {

static_assert(! AllGritful<Capsule<>, Capsule<int>>);

static_assert(! AllGritful<Shuttle<>, Shuttle<0>>);

static_assert(! AllGritful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllGritful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllGritful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllGritful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllGritful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllGritful<Travail<>, Travail<Phantom>>);

static_assert(! AllGritful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllGritful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllGritful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllGritful<Persist<>, Persist<Halcyon>>);

static_assert(! AllGritful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllGritful<Morning<>, Morning<Persist>>);

}}}}

#endif