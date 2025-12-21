// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MOLDFUL_H

#include "conceptrodon/omennivore/concepts/moldful.hpp"

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
namespace TestMoldful {

static_assert(Moldful<Capsule<>>);

static_assert(! Moldful<Shuttle<>>);

static_assert(! Moldful<Vehicle<>>);

static_assert(! Moldful<Carrier<>>);

static_assert(! Moldful<Reverie<>>);

static_assert(! Moldful<Phantom<>>);

static_assert(! Moldful<Forlorn<>>);

static_assert(! Moldful<Travail<>>);

static_assert(! Moldful<Lullaby<>>);

static_assert(! Moldful<Halcyon<>>);

static_assert(! Moldful<Pursuit<>>);

static_assert(! Moldful<Persist<>>);

static_assert(! Moldful<Sunrise<>>);

static_assert(! Moldful<Morning<>>);

}}}}

#endif