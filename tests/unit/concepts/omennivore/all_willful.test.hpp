// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_WILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_WILLFUL_H

#include "conceptrodon/omennivore/concepts/all_willful.hpp"

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