// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGEFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/pageful.hpp"

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
namespace TestPageful {

static_assert(! Pageful<Capsule<>>);

static_assert(Pageful<Shuttle<>>);

static_assert(! Pageful<Vehicle<>>);

static_assert(! Pageful<Carrier<>>);

static_assert(! Pageful<Reverie<>>);

static_assert(! Pageful<Phantom<>>);

static_assert(! Pageful<Forlorn<>>);

static_assert(! Pageful<Travail<>>);

static_assert(! Pageful<Lullaby<>>);

static_assert(! Pageful<Halcyon<>>);

static_assert(! Pageful<Pursuit<>>);

static_assert(! Pageful<Persist<>>);

static_assert(! Pageful<Sunrise<>>);

static_assert(! Pageful<Morning<>>);

}}}}

#endif