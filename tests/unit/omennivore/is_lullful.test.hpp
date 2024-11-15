// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_LULLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_LULLFUL_H

#include "conceptrodon/omennivore/is_lullful.hpp"

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
namespace TestIsLullful {

INVALID(IsLullful<Capsule<>>::value);
INVALID(IsLullful_v<Capsule<>>);

INVALID(IsLullful<Shuttle<>>::value);
INVALID(IsLullful_v<Shuttle<>>);

INVALID(IsLullful<Reverie<>>::value);
INVALID(IsLullful_v<Reverie<>>);

INVALID(IsLullful<Phantom<>>::value);
INVALID(IsLullful_v<Phantom<>>);

INVALID(IsLullful<Forlorn<>>::value);
INVALID(IsLullful_v<Forlorn<>>);

INVALID(IsLullful<Travail<>>::value);
INVALID(IsLullful_v<Travail<>>);

INVALID(IsLullful<Lullaby<>>::value);
INVALID(IsLullful_v<Lullaby<>>);

INVALID(IsLullful<Halcyon<>>::value);
INVALID(IsLullful_v<Halcyon<>>);

VALID(IsLullful<Pursuit<>>::value);
VALID(IsLullful_v<Pursuit<>>);

INVALID(IsLullful<Persist<>>::value);
INVALID(IsLullful_v<Persist<>>);

INVALID(IsLullful<Sunrise<>>::value);
INVALID(IsLullful_v<Sunrise<>>);

INVALID(IsLullful<Morning<>>::value);
INVALID(IsLullful_v<Morning<>>);

INVALID(IsLullful<Arcadia<>>::value);
INVALID(IsLullful_v<Arcadia<>>);

INVALID(IsLullful<Nirvana<>>::value);
INVALID(IsLullful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif