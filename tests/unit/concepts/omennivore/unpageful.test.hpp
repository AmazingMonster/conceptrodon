// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNPAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNPAGEFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/unpageful.hpp"

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