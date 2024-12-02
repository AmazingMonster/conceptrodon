// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_WILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_WILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_willful.hpp"

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
namespace TestAllWillful {

static_assert(! AllWillful<Capsule<>, Capsule<int>>);

static_assert(! AllWillful<Shuttle<>, Shuttle<0>>);

static_assert(! AllWillful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllWillful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllWillful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllWillful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllWillful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllWillful<Travail<>, Travail<Phantom>>);

static_assert(! AllWillful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllWillful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllWillful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllWillful<Persist<>, Persist<Halcyon>>);

static_assert(! AllWillful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllWillful<Morning<>, Morning<Persist>>);

}}}}

#endif