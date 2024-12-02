// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNWILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNWILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unwillful.hpp"

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
namespace TestAllUnwillful {

static_assert(AllUnwillful<Capsule<>, Capsule<int>>);

static_assert(AllUnwillful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnwillful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnwillful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnwillful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUnwillful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnwillful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnwillful<Travail<>, Travail<Phantom>>);

static_assert(AllUnwillful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnwillful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnwillful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllUnwillful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnwillful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnwillful<Morning<>, Morning<Persist>>);

}}}}

#endif