// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNGRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNGRITFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/ungritful.hpp"

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
namespace TestUngritful {

static_assert(Ungritful<Capsule<>>);

static_assert(Ungritful<Shuttle<>>);

static_assert(Ungritful<Vehicle<>>);

static_assert(Ungritful<Carrier<>>);

static_assert(Ungritful<Reverie<>>);

static_assert(Ungritful<Phantom<>>);

static_assert(Ungritful<Forlorn<>>);

static_assert(Ungritful<Travail<>>);

static_assert(Ungritful<Lullaby<>>);

static_assert(Ungritful<Halcyon<>>);

static_assert(! Ungritful<Pursuit<>>);

static_assert(Ungritful<Persist<>>);

static_assert(Ungritful<Sunrise<>>);

static_assert(Ungritful<Morning<>>);

}}}}

#endif