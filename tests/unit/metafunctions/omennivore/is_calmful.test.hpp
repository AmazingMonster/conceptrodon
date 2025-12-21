// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_CALMFUL_H

#include "conceptrodon/metafunctions/omennivore/is_calmful.hpp"

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
namespace TestIsCalmful {

INVALID(IsCalmful<Capsule<>>::value);
INVALID(IsCalmful_v<Capsule<>>);

INVALID(IsCalmful<Shuttle<>>::value);
INVALID(IsCalmful_v<Shuttle<>>);

INVALID(IsCalmful<Vehicle<>>::value);
INVALID(IsCalmful_v<Vehicle<>>);

INVALID(IsCalmful<Carrier<>>::value);
INVALID(IsCalmful_v<Carrier<>>);

INVALID(IsCalmful<Reverie<>>::value);
INVALID(IsCalmful_v<Reverie<>>);

INVALID(IsCalmful<Phantom<>>::value);
INVALID(IsCalmful_v<Phantom<>>);

INVALID(IsCalmful<Forlorn<>>::value);
INVALID(IsCalmful_v<Forlorn<>>);

INVALID(IsCalmful<Travail<>>::value);
INVALID(IsCalmful_v<Travail<>>);

INVALID(IsCalmful<Lullaby<>>::value);
INVALID(IsCalmful_v<Lullaby<>>);

VALID(IsCalmful<Halcyon<>>::value);
VALID(IsCalmful_v<Halcyon<>>);

INVALID(IsCalmful<Pursuit<>>::value);
INVALID(IsCalmful_v<Pursuit<>>);

INVALID(IsCalmful<Persist<>>::value);
INVALID(IsCalmful_v<Persist<>>);

INVALID(IsCalmful<Sunrise<>>::value);
INVALID(IsCalmful_v<Sunrise<>>);

INVALID(IsCalmful<Morning<>>::value);
INVALID(IsCalmful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif