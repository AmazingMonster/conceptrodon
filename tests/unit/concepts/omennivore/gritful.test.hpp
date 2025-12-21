// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITFUL_H

#include "conceptrodon/concepts/omennivore/gritful.hpp"

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
namespace TestGritful {

static_assert(! Gritful<Capsule<>>);

static_assert(! Gritful<Shuttle<>>);

static_assert(! Gritful<Vehicle<>>);

static_assert(! Gritful<Carrier<>>);

static_assert(! Gritful<Reverie<>>);

static_assert(! Gritful<Phantom<>>);

static_assert(! Gritful<Forlorn<>>);

static_assert(! Gritful<Travail<>>);

static_assert(! Gritful<Lullaby<>>);

static_assert(! Gritful<Halcyon<>>);

static_assert(Gritful<Pursuit<>>);

static_assert(! Gritful<Persist<>>);

static_assert(! Gritful<Sunrise<>>);

static_assert(! Gritful<Morning<>>);

}}}}

#endif