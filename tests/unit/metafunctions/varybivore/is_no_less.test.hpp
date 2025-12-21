// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_NO_LESS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_NO_LESS_H

#include "conceptrodon/metafunctions/varybivore/is_no_less.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsNoLess {




/******************************************************************************************************/
VALID(IsNoLess_v<0, 0, -1>);
VALID(IsNoLess<1, 0, -2>::value);
INVALID(IsNoLess_v<0, 1, 0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif