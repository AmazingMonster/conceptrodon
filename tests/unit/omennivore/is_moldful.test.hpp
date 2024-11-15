// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_MOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_MOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"

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
namespace TestIsMoldful {

VALID(IsMoldful<Capsule<>>::value);
VALID(IsMoldful_v<Capsule<>>);

INVALID(IsMoldful<Shuttle<>>::value);
INVALID(IsMoldful_v<Shuttle<>>);

INVALID(IsMoldful<Reverie<>>::value);
INVALID(IsMoldful_v<Reverie<>>);

INVALID(IsMoldful<Phantom<>>::value);
INVALID(IsMoldful_v<Phantom<>>);

INVALID(IsMoldful<Forlorn<>>::value);
INVALID(IsMoldful_v<Forlorn<>>);

INVALID(IsMoldful<Travail<>>::value);
INVALID(IsMoldful_v<Travail<>>);

INVALID(IsMoldful<Lullaby<>>::value);
INVALID(IsMoldful_v<Lullaby<>>);

INVALID(IsMoldful<Halcyon<>>::value);
INVALID(IsMoldful_v<Halcyon<>>);

INVALID(IsMoldful<Pursuit<>>::value);
INVALID(IsMoldful_v<Pursuit<>>);

INVALID(IsMoldful<Persist<>>::value);
INVALID(IsMoldful_v<Persist<>>);

INVALID(IsMoldful<Sunrise<>>::value);
INVALID(IsMoldful_v<Sunrise<>>);

INVALID(IsMoldful<Morning<>>::value);
INVALID(IsMoldful_v<Morning<>>);

INVALID(IsMoldful<Arcadia<>>::value);
INVALID(IsMoldful_v<Arcadia<>>);

INVALID(IsMoldful<Nirvana<>>::value);
INVALID(IsMoldful_v<Nirvana<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif