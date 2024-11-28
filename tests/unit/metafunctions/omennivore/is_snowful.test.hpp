// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_SNOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"

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