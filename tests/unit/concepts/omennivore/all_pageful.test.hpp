// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_PAGEFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_pageful.hpp"

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