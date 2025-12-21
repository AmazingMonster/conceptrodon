// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_DIFFERENT_FROM_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_DIFFERENT_FROM_H

#include "conceptrodon/metafunctions/typelivore/is_different_from.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestIsDifferentFrom {




/******************************************************************************************************/
INVALID(IsDifferentFrom<int>::Mold_v<int>);
VALID(IsDifferentFrom<int>::Mold_v<float>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif