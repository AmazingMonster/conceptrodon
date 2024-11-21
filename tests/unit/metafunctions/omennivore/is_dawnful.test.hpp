// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_DAWNFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_DAWNFUL_H

#include "conceptrodon/omennivore/is_dawnful.hpp"

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