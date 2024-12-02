// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNPAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNPAGEFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/unpageful.hpp"

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
namespace TestUnpageful {

static_assert(Unpageful<Capsule<>>);

static_assert(! Unpageful<Shuttle<>>);

static_assert(Unpageful<Vehicle<>>);

static_assert(Unpageful<Carrier<>>);

static_assert(Unpageful<Reverie<>>);

static_assert(Unpageful<Phantom<>>);

static_assert(Unpageful<Forlorn<>>);

static_assert(Unpageful<Travail<>>);

static_assert(Unpageful<Lullaby<>>);

static_assert(Unpageful<Halcyon<>>);

static_assert(Unpageful<Pursuit<>>);

static_assert(Unpageful<Persist<>>);

static_assert(Unpageful<Sunrise<>>);

static_assert(Unpageful<Morning<>>);

}}}}

#endif