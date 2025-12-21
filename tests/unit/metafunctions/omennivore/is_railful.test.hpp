// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_RAILFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_RAILFUL_H

#include "conceptrodon/metafunctions/omennivore/is_railful.hpp"

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