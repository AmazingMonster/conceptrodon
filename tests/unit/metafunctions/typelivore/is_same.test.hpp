// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_SAME_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_SAME_H

#include "conceptrodon/metafunctions/typelivore/is_same.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestIsSame {




/******************************************************************************************************/
INVALID(IsSame<int, int, double, int*>::value);
VALID(IsSame_v<int, int, int, int>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif