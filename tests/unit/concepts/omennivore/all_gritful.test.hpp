// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_GRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_GRITFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_gritful.hpp"

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