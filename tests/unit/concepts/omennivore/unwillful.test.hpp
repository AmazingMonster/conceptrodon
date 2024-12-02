// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNWILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNWILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/unwillful.hpp"

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
namespace TestUnwillful {

static_assert(Unwillful<Capsule<>>);

static_assert(Unwillful<Shuttle<>>);

static_assert(Unwillful<Vehicle<>>);

static_assert(Unwillful<Carrier<>>);

static_assert(Unwillful<Reverie<>>);

static_assert(Unwillful<Phantom<>>);

static_assert(Unwillful<Forlorn<>>);

static_assert(Unwillful<Travail<>>);

static_assert(Unwillful<Lullaby<>>);

static_assert(Unwillful<Halcyon<>>);

static_assert(Unwillful<Pursuit<>>);

static_assert(! Unwillful<Persist<>>);

static_assert(Unwillful<Sunrise<>>);

static_assert(Unwillful<Morning<>>);

}}}}

#endif