// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_DIFFERENT_H

#include "conceptrodon/typelivore/is_different.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestIsDifferent {




/******************************************************************************************************/
INVALID(IsDifferent<int, int, double, int*>::value);
VALID(IsDifferent_v<int, float, double, int*>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif