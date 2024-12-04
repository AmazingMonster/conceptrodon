// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_EQUAL_TO_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_EQUAL_TO_H

#include "conceptrodon/varybivore/are_equal_to.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreEqualTo {




/******************************************************************************************************/
VALID(AreEqualTo<0>::Page_v<0, 0.0>);
INVALID(AreEqualTo<0>::Page_v<1, 0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif