// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_SAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_SAILFUL_H

#include "conceptrodon/omennivore/is_sailful.hpp"

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
namespace TestIsSailful {

INVALID(IsSailful<Capsule<>>::value);
INVALID(IsSailful_v<Capsule<>>);

INVALID(IsSailful<Shuttle<>>::value);
INVALID(IsSailful_v<Shuttle<>>);

INVALID(IsSailful<Reverie<>>::value);
INVALID(IsSailful_v<Reverie<>>);

INVALID(IsSailful<Phantom<>>::value);
INVALID(IsSailful_v<Phantom<>>);

INVALID(IsSailful<Forlorn<>>::value);
INVALID(IsSailful_v<Forlorn<>>);

VALID(IsSailful<Travail<>>::value);
VALID(IsSailful_v<Travail<>>);

INVALID(IsSailful<Lullaby<>>::value);
INVALID(IsSailful_v<Lullaby<>>);

INVALID(IsSailful<Halcyon<>>::value);
INVALID(IsSailful_v<Halcyon<>>);

INVALID(IsSailful<Pursuit<>>::value);
INVALID(IsSailful_v<Pursuit<>>);

INVALID(IsSailful<Persist<>>::value);
INVALID(IsSailful_v<Persist<>>);

INVALID(IsSailful<Sunrise<>>::value);
INVALID(IsSailful_v<Sunrise<>>);

INVALID(IsSailful<Morning<>>::value);
INVALID(IsSailful_v<Morning<>>);

INVALID(IsSailful<Arcadia<>>::value);
INVALID(IsSailful_v<Arcadia<>>);

INVALID(IsSailful<Nirvana<>>::value);
INVALID(IsSailful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif