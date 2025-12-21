// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_POSITIVE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_POSITIVE_H

#include "conceptrodon/metafunctions/varybivore/positive.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestPositive {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -10

EQUAL_VALUE(Positive_v<-10>);
EQUAL_VALUE(Positive<-10.0>::value);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    10

EQUAL_VALUE(Positive_v<10>);
EQUAL_VALUE(Positive_v<10.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif