// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_IS_GRITFUL_H

#include "conceptrodon/metafunctions/omennivore/is_gritful.hpp"

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
namespace TestIsGritful {

INVALID(IsGritful<Capsule<>>::value);
INVALID(IsGritful_v<Capsule<>>);

INVALID(IsGritful<Shuttle<>>::value);
INVALID(IsGritful_v<Shuttle<>>);

INVALID(IsGritful<Vehicle<>>::value);
INVALID(IsGritful_v<Vehicle<>>);

INVALID(IsGritful<Carrier<>>::value);
INVALID(IsGritful_v<Carrier<>>);

INVALID(IsGritful<Reverie<>>::value);
INVALID(IsGritful_v<Reverie<>>);

INVALID(IsGritful<Phantom<>>::value);
INVALID(IsGritful_v<Phantom<>>);

INVALID(IsGritful<Forlorn<>>::value);
INVALID(IsGritful_v<Forlorn<>>);

INVALID(IsGritful<Travail<>>::value);
INVALID(IsGritful_v<Travail<>>);

INVALID(IsGritful<Lullaby<>>::value);
INVALID(IsGritful_v<Lullaby<>>);

INVALID(IsGritful<Halcyon<>>::value);
INVALID(IsGritful_v<Halcyon<>>);

VALID(IsGritful<Pursuit<>>::value);
VALID(IsGritful_v<Pursuit<>>);

INVALID(IsGritful<Persist<>>::value);
INVALID(IsGritful_v<Persist<>>);

INVALID(IsGritful<Sunrise<>>::value);
INVALID(IsGritful_v<Sunrise<>>);

INVALID(IsGritful<Morning<>>::value);
INVALID(IsGritful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif