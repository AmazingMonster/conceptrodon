// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"

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
namespace TestIsRoadful {

INVALID(IsRoadful<Capsule<>>::value);
INVALID(IsRoadful_v<Capsule<>>);

INVALID(IsRoadful<Shuttle<>>::value);
INVALID(IsRoadful_v<Shuttle<>>);

VALID(IsRoadful<Vehicle<>>::value);
VALID(IsRoadful_v<Vehicle<>>);

INVALID(IsRoadful<Carrier<>>::value);
INVALID(IsRoadful_v<Carrier<>>);

INVALID(IsRoadful<Reverie<>>::value);
INVALID(IsRoadful_v<Reverie<>>);

INVALID(IsRoadful<Phantom<>>::value);
INVALID(IsRoadful_v<Phantom<>>);

INVALID(IsRoadful<Forlorn<>>::value);
INVALID(IsRoadful_v<Forlorn<>>);

INVALID(IsRoadful<Travail<>>::value);
INVALID(IsRoadful_v<Travail<>>);

INVALID(IsRoadful<Lullaby<>>::value);
INVALID(IsRoadful_v<Lullaby<>>);

INVALID(IsRoadful<Halcyon<>>::value);
INVALID(IsRoadful_v<Halcyon<>>);

INVALID(IsRoadful<Pursuit<>>::value);
INVALID(IsRoadful_v<Pursuit<>>);

INVALID(IsRoadful<Persist<>>::value);
INVALID(IsRoadful_v<Persist<>>);

INVALID(IsRoadful<Sunrise<>>::value);
INVALID(IsRoadful_v<Sunrise<>>);

INVALID(IsRoadful<Morning<>>::value);
INVALID(IsRoadful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif