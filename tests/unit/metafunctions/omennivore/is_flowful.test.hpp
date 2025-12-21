// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_FLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_FLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"

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
namespace TestIsFlowful {

INVALID(IsFlowful<Capsule<>>::value);
INVALID(IsFlowful_v<Capsule<>>);

INVALID(IsFlowful<Shuttle<>>::value);
INVALID(IsFlowful_v<Shuttle<>>);

INVALID(IsFlowful<Vehicle<>>::value);
INVALID(IsFlowful_v<Vehicle<>>);

INVALID(IsFlowful<Carrier<>>::value);
INVALID(IsFlowful_v<Carrier<>>);

VALID(IsFlowful<Reverie<>>::value);
VALID(IsFlowful_v<Reverie<>>);

INVALID(IsFlowful<Phantom<>>::value);
INVALID(IsFlowful_v<Phantom<>>);

INVALID(IsFlowful<Forlorn<>>::value);
INVALID(IsFlowful_v<Forlorn<>>);

INVALID(IsFlowful<Travail<>>::value);
INVALID(IsFlowful_v<Travail<>>);

INVALID(IsFlowful<Lullaby<>>::value);
INVALID(IsFlowful_v<Lullaby<>>);

INVALID(IsFlowful<Halcyon<>>::value);
INVALID(IsFlowful_v<Halcyon<>>);

INVALID(IsFlowful<Pursuit<>>::value);
INVALID(IsFlowful_v<Pursuit<>>);

INVALID(IsFlowful<Persist<>>::value);
INVALID(IsFlowful_v<Persist<>>);

INVALID(IsFlowful<Sunrise<>>::value);
INVALID(IsFlowful_v<Sunrise<>>);

INVALID(IsFlowful<Morning<>>::value);
INVALID(IsFlowful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif