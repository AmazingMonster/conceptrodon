// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_NO_LESS_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_NO_LESS_THAN_H

#include "conceptrodon/metafunctions/varybivore/are_no_less_than.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreNoLessThan {




/******************************************************************************************************/
VALID(AreNoLessThan<0>::Page_v<0 , 1, 2, 3>);
VALID(AreNoLessThan<0>::Page<1, 1, 2>::value);
INVALID(AreNoLessThan<1>::Page_v<0, 1, 2>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif