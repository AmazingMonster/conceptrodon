// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_FLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_FLOWFUL_H

#include "conceptrodon/concepts/omennivore/all_flowful.hpp"

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
namespace TestAllFlowful {

static_assert(! AllFlowful<Capsule<>, Capsule<int>>);

static_assert(! AllFlowful<Shuttle<>, Shuttle<0>>);

static_assert(! AllFlowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllFlowful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllFlowful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllFlowful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllFlowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllFlowful<Travail<>, Travail<Phantom>>);

static_assert(! AllFlowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllFlowful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllFlowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllFlowful<Persist<>, Persist<Halcyon>>);

static_assert(! AllFlowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllFlowful<Morning<>, Morning<Persist>>);

}}}}

#endif