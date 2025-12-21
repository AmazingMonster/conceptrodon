// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SUBTRACT_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SUBTRACT_H

#include "conceptrodon/metafunctions/varybivore/subtract.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestSubtract {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    0

EQUAL_VALUE(Subtract_v<1, 1, 0>);
EQUAL_VALUE(Subtract_v<1, 1.0, -2, 2>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif