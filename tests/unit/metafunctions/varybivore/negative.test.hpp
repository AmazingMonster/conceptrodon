// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_NEGATIVE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_NEGATIVE_H

#include <concepts>
#include "conceptrodon/varybivore/negative.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestNegative {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -10
EQUAL_VALUE(Negative<10>::value);
EQUAL_VALUE(Negative_v<10.0>);
#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    10
EQUAL_VALUE(Negative_v<-10>);
EQUAL_VALUE(Negative_v<-10.0>);
#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif