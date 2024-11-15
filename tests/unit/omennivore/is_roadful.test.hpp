// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_ROADFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"

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
namespace TestIsRoadful {

INVALID(IsRoadful<Capsule<>>::value);
INVALID(IsRoadful_v<Capsule<>>);

INVALID(IsRoadful<Shuttle<>>::value);
INVALID(IsRoadful_v<Shuttle<>>);

VALID(IsRoadful<Reverie<>>::value);
VALID(IsRoadful_v<Reverie<>>);

INVALID(IsRoadful<Phantom<>>::value);
INVALID(IsRoadful_v<Phantom<>>);

INVALID(IsRoadful<Forlorn<>>::value);
INVALID(IsRoadful_v<Forlorn<>>);

INVALID(IsRoadful<Travail<>>::value);
INVALID(IsRoadful_v<Travail<>>);

INVALID(IsRoadful<Lullaby<>>::value);
INVALID(IsRoadful_v<Lullaby<>>);

INVALID(IsRoadful<Halcyon<>>::value);
INVALID(IsRoadful_v<Halcyon<>>);

INVALID(IsRoadful<Pursuit<>>::value);
INVALID(IsRoadful_v<Pursuit<>>);

INVALID(IsRoadful<Persist<>>::value);
INVALID(IsRoadful_v<Persist<>>);

INVALID(IsRoadful<Sunrise<>>::value);
INVALID(IsRoadful_v<Sunrise<>>);

INVALID(IsRoadful<Morning<>>::value);
INVALID(IsRoadful_v<Morning<>>);

INVALID(IsRoadful<Arcadia<>>::value);
INVALID(IsRoadful_v<Arcadia<>>);

INVALID(IsRoadful<Nirvana<>>::value);
INVALID(IsRoadful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif