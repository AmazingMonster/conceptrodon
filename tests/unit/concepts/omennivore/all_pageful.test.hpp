// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PAGEFUL_H

#include "conceptrodon/concepts/omennivore/all_pageful.hpp"

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
namespace TestAllPageful {

static_assert(! AllPageful<Capsule<>, Capsule<int>>);

static_assert(AllPageful<Shuttle<>, Shuttle<0>>);

static_assert(! AllPageful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllPageful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllPageful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllPageful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllPageful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllPageful<Travail<>, Travail<Phantom>>);

static_assert(! AllPageful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllPageful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllPageful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllPageful<Persist<>, Persist<Halcyon>>);

static_assert(! AllPageful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllPageful<Morning<>, Morning<Persist>>);

}}}}

#endif