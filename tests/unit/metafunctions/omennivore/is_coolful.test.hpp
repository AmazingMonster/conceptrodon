// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_COOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_COOLFUL_H

#include "conceptrodon/omennivore/is_coolful.hpp"

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
namespace TestIsCoolful {

INVALID(IsCoolful<Capsule<>>::value);
INVALID(IsCoolful_v<Capsule<>>);

INVALID(IsCoolful<Shuttle<>>::value);
INVALID(IsCoolful_v<Shuttle<>>);

INVALID(IsCoolful<Vehicle<>>::value);
INVALID(IsCoolful_v<Vehicle<>>);

INVALID(IsCoolful<Carrier<>>::value);
INVALID(IsCoolful_v<Carrier<>>);

INVALID(IsCoolful<Reverie<>>::value);
INVALID(IsCoolful_v<Reverie<>>);

INVALID(IsCoolful<Phantom<>>::value);
INVALID(IsCoolful_v<Phantom<>>);

INVALID(IsCoolful<Forlorn<>>::value);
INVALID(IsCoolful_v<Forlorn<>>);

INVALID(IsCoolful<Travail<>>::value);
INVALID(IsCoolful_v<Travail<>>);

VALID(IsCoolful<Lullaby<>>::value);
VALID(IsCoolful_v<Lullaby<>>);

INVALID(IsCoolful<Halcyon<>>::value);
INVALID(IsCoolful_v<Halcyon<>>);

INVALID(IsCoolful<Pursuit<>>::value);
INVALID(IsCoolful_v<Pursuit<>>);

INVALID(IsCoolful<Persist<>>::value);
INVALID(IsCoolful_v<Persist<>>);

INVALID(IsCoolful<Sunrise<>>::value);
INVALID(IsCoolful_v<Sunrise<>>);

INVALID(IsCoolful<Morning<>>::value);
INVALID(IsCoolful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif