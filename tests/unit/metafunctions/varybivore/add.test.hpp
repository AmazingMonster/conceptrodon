// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ADD_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ADD_H

#include "conceptrodon/metafunctions/varybivore/add.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAdd {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    6

EQUAL_VALUE(Add_v<1, 2, 3>);
EQUAL_VALUE(Add_v<1, 2.0, 3>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif