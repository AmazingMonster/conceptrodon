// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNMOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNMOLDFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/unmoldful.hpp"

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
namespace TestUnmoldful {

static_assert(! Unmoldful<Capsule<>>);

static_assert(Unmoldful<Shuttle<>>);

static_assert(Unmoldful<Vehicle<>>);

static_assert(Unmoldful<Carrier<>>);

static_assert(Unmoldful<Reverie<>>);

static_assert(Unmoldful<Phantom<>>);

static_assert(Unmoldful<Forlorn<>>);

static_assert(Unmoldful<Travail<>>);

static_assert(Unmoldful<Lullaby<>>);

static_assert(Unmoldful<Halcyon<>>);

static_assert(Unmoldful<Pursuit<>>);

static_assert(Unmoldful<Persist<>>);

static_assert(Unmoldful<Sunrise<>>);

static_assert(Unmoldful<Morning<>>);

}}}}

#endif