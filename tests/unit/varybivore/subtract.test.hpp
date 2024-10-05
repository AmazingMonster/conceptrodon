// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_SUBTRACT_H
#define CONCEPTRODON_VARYBIVORE_TEST_SUBTRACT_H

#include <concepts>
#include "conceptrodon/varybivore/subtract.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestSubtract {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    0

EQUAL_VALUE(Subtract_v<1, 1>);
EQUAL_VALUE(Subtract_v<1, 1.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -1

EQUAL_VALUE(SubtractFrom<1>::Page_v<2>);
EQUAL_VALUE(SubtractFrom<1>::Page_v<2.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif