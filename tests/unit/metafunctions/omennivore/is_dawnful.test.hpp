// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_DAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_DAWNFUL_H

#include "conceptrodon/metafunctions/omennivore/is_dawnful.hpp"

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
namespace TestIsDawnful {

INVALID(IsDawnful<Capsule<>>::value);
INVALID(IsDawnful_v<Capsule<>>);

INVALID(IsDawnful<Shuttle<>>::value);
INVALID(IsDawnful_v<Shuttle<>>);

INVALID(IsDawnful<Vehicle<>>::value);
INVALID(IsDawnful_v<Vehicle<>>);

INVALID(IsDawnful<Carrier<>>::value);
INVALID(IsDawnful_v<Carrier<>>);

INVALID(IsDawnful<Reverie<>>::value);
INVALID(IsDawnful_v<Reverie<>>);

INVALID(IsDawnful<Phantom<>>::value);
INVALID(IsDawnful_v<Phantom<>>);

INVALID(IsDawnful<Forlorn<>>::value);
INVALID(IsDawnful_v<Forlorn<>>);

INVALID(IsDawnful<Travail<>>::value);
INVALID(IsDawnful_v<Travail<>>);

INVALID(IsDawnful<Lullaby<>>::value);
INVALID(IsDawnful_v<Lullaby<>>);

INVALID(IsDawnful<Halcyon<>>::value);
INVALID(IsDawnful_v<Halcyon<>>);

INVALID(IsDawnful<Pursuit<>>::value);
INVALID(IsDawnful_v<Pursuit<>>);

INVALID(IsDawnful<Persist<>>::value);
INVALID(IsDawnful_v<Persist<>>);

INVALID(IsDawnful<Sunrise<>>::value);
INVALID(IsDawnful_v<Sunrise<>>);

VALID(IsDawnful<Morning<>>::value);
VALID(IsDawnful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif