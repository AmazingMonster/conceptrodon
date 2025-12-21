// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNWILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNWILLFUL_H

#include "conceptrodon/concepts/omennivore/unwillful.hpp"

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