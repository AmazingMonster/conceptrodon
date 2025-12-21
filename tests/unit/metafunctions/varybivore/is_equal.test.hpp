// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_IS_EQUAL_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_IS_EQUAL_H

#include "conceptrodon/metafunctions/varybivore/is_equal.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsEqual {




/******************************************************************************************************/
VALID(IsEqual_v<0, 0, 0.0>);
VALID(IsEqual_v<1, 1.0, 1.0>);
INVALID(IsEqual_v<0, 1, 1>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif