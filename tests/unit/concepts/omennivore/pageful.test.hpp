// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGEFUL_H

#include "conceptrodon/descend/omennivore/concepts/pageful.hpp"

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