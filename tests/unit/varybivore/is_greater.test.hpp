// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_GREATER_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_GREATER_H

#include <concepts>
#include "conceptrodon/varybivore/is_greater.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsGreater {




/******************************************************************************************************/
INVALID(IsGreater_v<0, 0>);
VALID(IsGreater_v<1, 0>);
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(IsGreaterThan<0>::Page_v<0>);
VALID(IsGreaterThan<0>::Page_v<1>);
INVALID(IsGreaterThan<1>::Page_v<0>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif