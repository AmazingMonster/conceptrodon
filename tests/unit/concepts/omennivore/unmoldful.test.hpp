// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNMOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNMOLDFUL_H

#include "conceptrodon/concepts/omennivore/unmoldful.hpp"

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