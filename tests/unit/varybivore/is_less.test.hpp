// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_LESS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_LESS_H

#include <concepts>
#include "conceptrodon/varybivore/is_less.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsLess {




/******************************************************************************************************/
INVALID(IsLess_v<0, 0>);
VALID(IsLess_v<0, 1>);
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(IsLessThan<0>::Page_v<0>);
INVALID(IsLessThan<0>::Page_v<1>);
VALID(IsLessThan<1>::Page_v<0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif