// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_GLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_GLOWFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_glowful.hpp"

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
namespace TestAllGlowful {

static_assert(! AllGlowful<Capsule<>, Capsule<int>>);

static_assert(! AllGlowful<Shuttle<>, Shuttle<0>>);

static_assert(! AllGlowful<Vehicle<>, Vehicle<Capsule>>);

static_assert(! AllGlowful<Carrier<>, Carrier<Shuttle>>);

static_assert(! AllGlowful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllGlowful<Phantom<>, Phantom<Carrier>>);

static_assert(! AllGlowful<Forlorn<>, Forlorn<Reverie>>);

static_assert(! AllGlowful<Travail<>, Travail<Phantom>>);

static_assert(! AllGlowful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllGlowful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllGlowful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(! AllGlowful<Persist<>, Persist<Halcyon>>);

static_assert(AllGlowful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(! AllGlowful<Morning<>, Morning<Persist>>);

}}}}

#endif