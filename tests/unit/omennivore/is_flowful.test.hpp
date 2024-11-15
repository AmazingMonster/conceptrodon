// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_FLOWFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_FLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
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
#include "conceptrodon/arcadia.hpp"
#include "conceptrodon/nirvana.hpp"

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

INVALID(IsFlowful<Reverie<>>::value);
INVALID(IsFlowful_v<Reverie<>>);

INVALID(IsFlowful<Phantom<>>::value);
INVALID(IsFlowful_v<Phantom<>>);

VALID(IsFlowful<Forlorn<>>::value);
VALID(IsFlowful_v<Forlorn<>>);

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

INVALID(IsFlowful<Arcadia<>>::value);
INVALID(IsFlowful_v<Arcadia<>>);

INVALID(IsFlowful<Nirvana<>>::value);
INVALID(IsFlowful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif