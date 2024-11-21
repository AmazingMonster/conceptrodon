// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_RAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_RAILFUL_H

#include "conceptrodon/omennivore/is_railful.hpp"

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
namespace TestIsRailful {

INVALID(IsRailful<Capsule<>>::value);
INVALID(IsRailful_v<Capsule<>>);

INVALID(IsRailful<Shuttle<>>::value);
INVALID(IsRailful_v<Shuttle<>>);

INVALID(IsRailful<Vehicle<>>::value);
INVALID(IsRailful_v<Vehicle<>>);

VALID(IsRailful<Carrier<>>::value);
VALID(IsRailful_v<Carrier<>>);

INVALID(IsRailful<Reverie<>>::value);
INVALID(IsRailful_v<Reverie<>>);

INVALID(IsRailful<Phantom<>>::value);
INVALID(IsRailful_v<Phantom<>>);

INVALID(IsRailful<Forlorn<>>::value);
INVALID(IsRailful_v<Forlorn<>>);

INVALID(IsRailful<Travail<>>::value);
INVALID(IsRailful_v<Travail<>>);

INVALID(IsRailful<Lullaby<>>::value);
INVALID(IsRailful_v<Lullaby<>>);

INVALID(IsRailful<Halcyon<>>::value);
INVALID(IsRailful_v<Halcyon<>>);

INVALID(IsRailful<Pursuit<>>::value);
INVALID(IsRailful_v<Pursuit<>>);

INVALID(IsRailful<Persist<>>::value);
INVALID(IsRailful_v<Persist<>>);

INVALID(IsRailful<Sunrise<>>::value);
INVALID(IsRailful_v<Sunrise<>>);

INVALID(IsRailful<Morning<>>::value);
INVALID(IsRailful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif