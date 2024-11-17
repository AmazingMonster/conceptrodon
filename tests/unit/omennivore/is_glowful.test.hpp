// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_GLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_GLOWFUL_H

#include "conceptrodon/omennivore/is_glowful.hpp"

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

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestIsGlowful {

INVALID(IsGlowful<Capsule<>>::value);
INVALID(IsGlowful_v<Capsule<>>);

INVALID(IsGlowful<Shuttle<>>::value);
INVALID(IsGlowful_v<Shuttle<>>);

INVALID(IsGlowful<Vehicle<>>::value);
INVALID(IsGlowful_v<Vehicle<>>);

INVALID(IsGlowful<Carrier<>>::value);
INVALID(IsGlowful_v<Carrier<>>);

INVALID(IsGlowful<Reverie<>>::value);
INVALID(IsGlowful_v<Reverie<>>);

INVALID(IsGlowful<Phantom<>>::value);
INVALID(IsGlowful_v<Phantom<>>);

INVALID(IsGlowful<Forlorn<>>::value);
INVALID(IsGlowful_v<Forlorn<>>);

INVALID(IsGlowful<Travail<>>::value);
INVALID(IsGlowful_v<Travail<>>);

INVALID(IsGlowful<Lullaby<>>::value);
INVALID(IsGlowful_v<Lullaby<>>);

INVALID(IsGlowful<Halcyon<>>::value);
INVALID(IsGlowful_v<Halcyon<>>);

INVALID(IsGlowful<Pursuit<>>::value);
INVALID(IsGlowful_v<Pursuit<>>);

INVALID(IsGlowful<Persist<>>::value);
INVALID(IsGlowful_v<Persist<>>);

VALID(IsGlowful<Sunrise<>>::value);
VALID(IsGlowful_v<Sunrise<>>);

INVALID(IsGlowful<Morning<>>::value);
INVALID(IsGlowful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif