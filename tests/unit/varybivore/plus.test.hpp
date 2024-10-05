// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_PLUS_H
#define CONCEPTRODON_VARYBIVORE_TEST_PLUS_H

#include <concepts>
#include "conceptrodon/varybivore/plus.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestPlus {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -10
EQUAL_VALUE(Plus_v<-10>);
EQUAL_VALUE(Plus_v<-10.0>);
#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    10
EQUAL_VALUE(Plus_v<10>);
EQUAL_VALUE(Plus_v<10.0>);
#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif