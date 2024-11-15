// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_WILLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_WILLFUL_H

#include "conceptrodon/omennivore/is_willful.hpp"

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
namespace TestIsWillful {

INVALID(IsWillful<Capsule<>>::value);
INVALID(IsWillful_v<Capsule<>>);

INVALID(IsWillful<Shuttle<>>::value);
INVALID(IsWillful_v<Shuttle<>>);

INVALID(IsWillful<Reverie<>>::value);
INVALID(IsWillful_v<Reverie<>>);

INVALID(IsWillful<Phantom<>>::value);
INVALID(IsWillful_v<Phantom<>>);

INVALID(IsWillful<Forlorn<>>::value);
INVALID(IsWillful_v<Forlorn<>>);

INVALID(IsWillful<Travail<>>::value);
INVALID(IsWillful_v<Travail<>>);

INVALID(IsWillful<Lullaby<>>::value);
INVALID(IsWillful_v<Lullaby<>>);

INVALID(IsWillful<Halcyon<>>::value);
INVALID(IsWillful_v<Halcyon<>>);

INVALID(IsWillful<Pursuit<>>::value);
INVALID(IsWillful_v<Pursuit<>>);

INVALID(IsWillful<Persist<>>::value);
INVALID(IsWillful_v<Persist<>>);

INVALID(IsWillful<Sunrise<>>::value);
INVALID(IsWillful_v<Sunrise<>>);

VALID(IsWillful<Morning<>>::value);
VALID(IsWillful_v<Morning<>>);

INVALID(IsWillful<Arcadia<>>::value);
INVALID(IsWillful_v<Arcadia<>>);

INVALID(IsWillful<Nirvana<>>::value);
INVALID(IsWillful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif