// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_SAILFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_SAILFUL_H

#include "conceptrodon/metafunctions/omennivore/is_sailful.hpp"

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
namespace TestIsSailful {

INVALID(IsSailful<Capsule<>>::value);
INVALID(IsSailful_v<Capsule<>>);

INVALID(IsSailful<Shuttle<>>::value);
INVALID(IsSailful_v<Shuttle<>>);

INVALID(IsSailful<Vehicle<>>::value);
INVALID(IsSailful_v<Vehicle<>>);

INVALID(IsSailful<Carrier<>>::value);
INVALID(IsSailful_v<Carrier<>>);

INVALID(IsSailful<Reverie<>>::value);
INVALID(IsSailful_v<Reverie<>>);

VALID(IsSailful<Phantom<>>::value);
VALID(IsSailful_v<Phantom<>>);

INVALID(IsSailful<Forlorn<>>::value);
INVALID(IsSailful_v<Forlorn<>>);

INVALID(IsSailful<Travail<>>::value);
INVALID(IsSailful_v<Travail<>>);

INVALID(IsSailful<Lullaby<>>::value);
INVALID(IsSailful_v<Lullaby<>>);

INVALID(IsSailful<Halcyon<>>::value);
INVALID(IsSailful_v<Halcyon<>>);

INVALID(IsSailful<Pursuit<>>::value);
INVALID(IsSailful_v<Pursuit<>>);

INVALID(IsSailful<Persist<>>::value);
INVALID(IsSailful_v<Persist<>>);

INVALID(IsSailful<Sunrise<>>::value);
INVALID(IsSailful_v<Sunrise<>>);

INVALID(IsSailful<Morning<>>::value);
INVALID(IsSailful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif