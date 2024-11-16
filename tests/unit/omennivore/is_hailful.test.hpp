// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_HAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_HAILFUL_H

#include "conceptrodon/omennivore/is_hailful.hpp"

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
namespace TestIsHailful {

INVALID(IsHailful<Capsule<>>::value);
INVALID(IsHailful_v<Capsule<>>);

INVALID(IsHailful<Shuttle<>>::value);
INVALID(IsHailful_v<Shuttle<>>);

INVALID(IsHailful<Reverie<>>::value);
INVALID(IsHailful_v<Reverie<>>);

INVALID(IsHailful<Phantom<>>::value);
INVALID(IsHailful_v<Phantom<>>);

INVALID(IsHailful<Forlorn<>>::value);
INVALID(IsHailful_v<Forlorn<>>);

INVALID(IsHailful<Travail<>>::value);
INVALID(IsHailful_v<Travail<>>);

INVALID(IsHailful<Lullaby<>>::value);
INVALID(IsHailful_v<Lullaby<>>);

VALID(IsHailful<Halcyon<>>::value);
VALID(IsHailful_v<Halcyon<>>);

INVALID(IsHailful<Pursuit<>>::value);
INVALID(IsHailful_v<Pursuit<>>);

INVALID(IsHailful<Persist<>>::value);
INVALID(IsHailful_v<Persist<>>);

INVALID(IsHailful<Sunrise<>>::value);
INVALID(IsHailful_v<Sunrise<>>);

INVALID(IsHailful<Morning<>>::value);
INVALID(IsHailful_v<Morning<>>);

INVALID(IsHailful<Arcadia<>>::value);
INVALID(IsHailful_v<Arcadia<>>);

INVALID(IsHailful<Nirvana<>>::value);
INVALID(IsHailful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif