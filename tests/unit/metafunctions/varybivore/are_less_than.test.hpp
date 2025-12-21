// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ARE_LESS_THAN_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ARE_LESS_THAN_H

#include "conceptrodon/metafunctions/varybivore/are_less_than.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreLessThan {




/******************************************************************************************************/
INVALID(AreLessThan<0>::Page<0, -1>::value);
INVALID(AreLessThan<1>::Page_v<3>);
VALID(AreLessThan<1>::Page_v<0, -1, -2>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif