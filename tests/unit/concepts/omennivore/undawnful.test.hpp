// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNDAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNDAWNFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/undawnful.hpp"

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
namespace TestUndawnful {

static_assert(Undawnful<Capsule<>>);

static_assert(Undawnful<Shuttle<>>);

static_assert(Undawnful<Vehicle<>>);

static_assert(Undawnful<Carrier<>>);

static_assert(Undawnful<Reverie<>>);

static_assert(Undawnful<Phantom<>>);

static_assert(Undawnful<Forlorn<>>);

static_assert(Undawnful<Travail<>>);

static_assert(Undawnful<Lullaby<>>);

static_assert(Undawnful<Halcyon<>>);

static_assert(Undawnful<Pursuit<>>);

static_assert(Undawnful<Persist<>>);

static_assert(Undawnful<Sunrise<>>);

static_assert(! Undawnful<Morning<>>);

}}}}

#endif