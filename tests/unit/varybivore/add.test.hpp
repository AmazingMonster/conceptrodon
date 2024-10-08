// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ADD_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ADD_H

#include <concepts>
#include "conceptrodon/varybivore/add.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAdd {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2

EQUAL_VALUE(Add_v<1, 1>);
EQUAL_VALUE(Add_v<1, 1.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2.0

EQUAL_VALUE(AddTo<1>::Page_v<1>);
EQUAL_VALUE(AddTo<1>::Page_v<1.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif