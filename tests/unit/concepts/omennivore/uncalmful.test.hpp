// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNCALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_UNCALMFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/uncalmful.hpp"

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
namespace TestUncalmful {

static_assert(Uncalmful<Capsule<>>);

static_assert(Uncalmful<Shuttle<>>);

static_assert(Uncalmful<Vehicle<>>);

static_assert(Uncalmful<Carrier<>>);

static_assert(Uncalmful<Reverie<>>);

static_assert(Uncalmful<Phantom<>>);

static_assert(Uncalmful<Forlorn<>>);

static_assert(Uncalmful<Travail<>>);

static_assert(Uncalmful<Lullaby<>>);

static_assert(! Uncalmful<Halcyon<>>);

static_assert(Uncalmful<Pursuit<>>);

static_assert(Uncalmful<Persist<>>);

static_assert(Uncalmful<Sunrise<>>);

static_assert(Uncalmful<Morning<>>);

}}}}

#endif