// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_UNEQUAL_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_UNEQUAL_H

#include <concepts>
#include "conceptrodon/varybivore/is_unequal.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsUnequal {




/******************************************************************************************************/
INVALID(IsUnequal_v<0, 0, 2, 3>);
VALID(IsUnequal_v<0, 1, 1, 2>);
VALID(IsUnequal<0, 1, 1, 2>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif