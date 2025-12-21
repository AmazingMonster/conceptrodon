// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_MAXIMUM_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_MAXIMUM_H

#include "conceptrodon/metafunctions/varybivore/maximum.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestMaximum {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    12

EQUAL_VALUE(Maximum_v<-10, 11, 12>);
EQUAL_VALUE(Maximum<-10, 11, 12>::value);
EQUAL_VALUE(Maximum_v<-10.0, -9.0, -8.5, 12.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif