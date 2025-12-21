// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_WILLFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_WILLFUL_H

#include "conceptrodon/metafunctions/omennivore/is_willful.hpp"

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
namespace TestIsWillful {

INVALID(IsWillful<Capsule<>>::value);
INVALID(IsWillful_v<Capsule<>>);

INVALID(IsWillful<Shuttle<>>::value);
INVALID(IsWillful_v<Shuttle<>>);

INVALID(IsWillful<Vehicle<>>::value);
INVALID(IsWillful_v<Vehicle<>>);

INVALID(IsWillful<Carrier<>>::value);
INVALID(IsWillful_v<Carrier<>>);

INVALID(IsWillful<Reverie<>>::value);
INVALID(IsWillful_v<Reverie<>>);

INVALID(IsWillful<Phantom<>>::value);
INVALID(IsWillful_v<Phantom<>>);

INVALID(IsWillful<Forlorn<>>::value);
INVALID(IsWillful_v<Forlorn<>>);

INVALID(IsWillful<Travail<>>::value);
INVALID(IsWillful_v<Travail<>>);

INVALID(IsWillful<Lullaby<>>::value);
INVALID(IsWillful_v<Lullaby<>>);

INVALID(IsWillful<Halcyon<>>::value);
INVALID(IsWillful_v<Halcyon<>>);

INVALID(IsWillful<Pursuit<>>::value);
INVALID(IsWillful_v<Pursuit<>>);

VALID(IsWillful<Persist<>>::value);
VALID(IsWillful_v<Persist<>>);

INVALID(IsWillful<Sunrise<>>::value);
INVALID(IsWillful_v<Sunrise<>>);

INVALID(IsWillful<Morning<>>::value);
INVALID(IsWillful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif