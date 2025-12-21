// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_UNEQUAL_TO_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_UNEQUAL_TO_H

#include "conceptrodon/metafunctions/varybivore/are_unequal_to.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreUnequalTo {




/******************************************************************************************************/
INVALID(AreUnequalTo<0>::Page_v<0, 1, 2>);
VALID(AreUnequalTo<0>::Page_v<1, 2, 3>);
VALID(AreUnequalTo<0>::Page<1, 2, 3>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif