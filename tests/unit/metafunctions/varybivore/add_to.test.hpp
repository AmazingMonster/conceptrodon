// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ADD_TO_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ADD_TO_H

#include "conceptrodon/metafunctions/varybivore/add_to.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAddTo {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    6

EQUAL_VALUE(AddTo<3>::Page_v<1, 2>);
EQUAL_VALUE(AddTo<3>::Page_v<1.0, 2>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif