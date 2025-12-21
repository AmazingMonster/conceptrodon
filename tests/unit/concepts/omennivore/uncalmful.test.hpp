// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNCALMFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_UNCALMFUL_H

#include "conceptrodon/concepts/omennivore/uncalmful.hpp"

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