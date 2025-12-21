// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_PAGEFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_PAGEFUL_H

#include "conceptrodon/omennivore/is_pageful.hpp"

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
namespace TestIsPageful {

INVALID(IsPageful<Capsule<>>::value);
INVALID(IsPageful_v<Capsule<>>);

VALID(IsPageful<Shuttle<>>::value);
VALID(IsPageful_v<Shuttle<>>);

INVALID(IsPageful<Vehicle<>>::value);
INVALID(IsPageful_v<Vehicle<>>);

INVALID(IsPageful<Carrier<>>::value);
INVALID(IsPageful_v<Carrier<>>);

INVALID(IsPageful<Reverie<>>::value);
INVALID(IsPageful_v<Reverie<>>);

INVALID(IsPageful<Phantom<>>::value);
INVALID(IsPageful_v<Phantom<>>);

INVALID(IsPageful<Forlorn<>>::value);
INVALID(IsPageful_v<Forlorn<>>);

INVALID(IsPageful<Travail<>>::value);
INVALID(IsPageful_v<Travail<>>);

INVALID(IsPageful<Lullaby<>>::value);
INVALID(IsPageful_v<Lullaby<>>);

INVALID(IsPageful<Halcyon<>>::value);
INVALID(IsPageful_v<Halcyon<>>);

INVALID(IsPageful<Pursuit<>>::value);
INVALID(IsPageful_v<Pursuit<>>);

INVALID(IsPageful<Persist<>>::value);
INVALID(IsPageful_v<Persist<>>);

INVALID(IsPageful<Sunrise<>>::value);
INVALID(IsPageful_v<Sunrise<>>);

INVALID(IsPageful<Morning<>>::value);
INVALID(IsPageful_v<Morning<>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif