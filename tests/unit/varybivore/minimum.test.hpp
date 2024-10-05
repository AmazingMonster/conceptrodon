// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_MINIMUM_H
#define CONCEPTRODON_VARYBIVORE_TEST_MINIMUM_H

#include <concepts>
#include "conceptrodon/varybivore/minimum.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestMinimum {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -10
EQUAL_VALUE(Minimum_v<-10, 11, 12>);
EQUAL_VALUE(Minimum_v<-10.0, -9.0, -8.5, static_cast<double>(7)>);
#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif