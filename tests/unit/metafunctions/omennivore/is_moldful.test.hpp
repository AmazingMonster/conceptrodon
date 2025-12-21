// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_MOLDFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_MOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"

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
namespace TestIsMoldful {

VALID(IsMoldful<Capsule<>>::value);
VALID(IsMoldful_v<Capsule<>>);

INVALID(IsMoldful<Shuttle<>>::value);
INVALID(IsMoldful_v<Shuttle<>>);

INVALID(IsMoldful<Vehicle<>>::value);
INVALID(IsMoldful_v<Vehicle<>>);

INVALID(IsMoldful<Carrier<>>::value);
INVALID(IsMoldful_v<Carrier<>>);

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

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif