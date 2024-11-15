// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_GRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_GRITFUL_H

#include "conceptrodon/omennivore/is_gritful.hpp"

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
namespace TestIsGritful {

INVALID(IsGritful<Capsule<>>::value);
INVALID(IsGritful_v<Capsule<>>);

INVALID(IsGritful<Shuttle<>>::value);
INVALID(IsGritful_v<Shuttle<>>);

INVALID(IsGritful<Reverie<>>::value);
INVALID(IsGritful_v<Reverie<>>);

INVALID(IsGritful<Phantom<>>::value);
INVALID(IsGritful_v<Phantom<>>);

INVALID(IsGritful<Forlorn<>>::value);
INVALID(IsGritful_v<Forlorn<>>);

INVALID(IsGritful<Travail<>>::value);
INVALID(IsGritful_v<Travail<>>);

INVALID(IsGritful<Lullaby<>>::value);
INVALID(IsGritful_v<Lullaby<>>);

INVALID(IsGritful<Halcyon<>>::value);
INVALID(IsGritful_v<Halcyon<>>);

INVALID(IsGritful<Pursuit<>>::value);
INVALID(IsGritful_v<Pursuit<>>);

INVALID(IsGritful<Persist<>>::value);
INVALID(IsGritful_v<Persist<>>);

VALID(IsGritful<Sunrise<>>::value);
VALID(IsGritful_v<Sunrise<>>);

INVALID(IsGritful<Morning<>>::value);
INVALID(IsGritful_v<Morning<>>);

INVALID(IsGritful<Arcadia<>>::value);
INVALID(IsGritful_v<Arcadia<>>);

INVALID(IsGritful<Nirvana<>>::value);
INVALID(IsGritful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif