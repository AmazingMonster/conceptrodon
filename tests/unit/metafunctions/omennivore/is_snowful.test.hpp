// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"

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
namespace TestIsSnowful {

INVALID(IsSnowful<Capsule<>>::value);
INVALID(IsSnowful_v<Capsule<>>);

INVALID(IsSnowful<Shuttle<>>::value);
INVALID(IsSnowful_v<Shuttle<>>);

INVALID(IsSnowful<Vehicle<>>::value);
INVALID(IsSnowful_v<Vehicle<>>);

INVALID(IsSnowful<Carrier<>>::value);
INVALID(IsSnowful_v<Carrier<>>);

INVALID(IsSnowful<Reverie<>>::value);
INVALID(IsSnowful_v<Reverie<>>);

INVALID(IsSnowful<Phantom<>>::value);
INVALID(IsSnowful_v<Phantom<>>);

VALID(IsSnowful<Forlorn<>>::value);
VALID(IsSnowful_v<Forlorn<>>);

INVALID(IsSnowful<Travail<>>::value);
INVALID(IsSnowful_v<Travail<>>);

INVALID(IsSnowful<Lullaby<>>::value);
INVALID(IsSnowful_v<Lullaby<>>);

INVALID(IsSnowful<Halcyon<>>::value);
INVALID(IsSnowful_v<Halcyon<>>);

INVALID(IsSnowful<Pursuit<>>::value);
INVALID(IsSnowful_v<Pursuit<>>);

INVALID(IsSnowful<Persist<>>::value);
INVALID(IsSnowful_v<Persist<>>);

INVALID(IsSnowful<Sunrise<>>::value);
INVALID(IsSnowful_v<Sunrise<>>);

INVALID(IsSnowful<Morning<>>::value);
INVALID(IsSnowful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif