// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SUBTRACT_FROM_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SUBTRACT_FROM_H

#include "conceptrodon/varybivore/subtract_from.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestSubtractFrom {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -1

EQUAL_VALUE(SubtractFrom<3>::Page_v<2, 2>);
EQUAL_VALUE(SubtractFrom<4>::Page_v<2.0, 3>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif