// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_CALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_CALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"

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