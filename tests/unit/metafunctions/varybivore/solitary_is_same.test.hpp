// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_SOLITARY_IS_SAME_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_SOLITARY_IS_SAME_H

#include "conceptrodon/metafunctions/varybivore/solitary_is_same.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsSame {




/******************************************************************************************************/
VALID(SolitaryIsSame_v<1, 1>);
INVALID(SolitaryIsSame_v<1, 2>);
INVALID(SolitaryIsSame<1, 1.0>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif