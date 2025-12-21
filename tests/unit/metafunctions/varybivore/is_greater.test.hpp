// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_GREATER_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_GREATER_H

#include "conceptrodon/metafunctions/varybivore/is_greater.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsGreater {




/******************************************************************************************************/
VALID(IsGreater<4, 1, 2.0, 3>::value);
INVALID(IsGreater<0, 0, 2, 3>::value);
INVALID(IsGreater_v<0, -1, 2, 3>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif