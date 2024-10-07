// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_DIFFERENT_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/typelivore/is_different.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace TestIsDifferent {




/******************************************************************************************************/
INVALID(IsDifferent_v<int, int>);
VALID(IsDifferent_v<int, float>);
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(IsDifferentAs<int>::Mold_v<int>);
VALID(IsDifferentAs<int>::Mold_v<float>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif