// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_GLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_GLOWFUL_H

#include "conceptrodon/metafunctions/omennivore/is_glowful.hpp"

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