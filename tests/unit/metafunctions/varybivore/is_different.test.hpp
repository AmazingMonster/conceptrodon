// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_DIFFERENT_H

#include "conceptrodon/metafunctions/varybivore/is_different.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsDifferent {




/******************************************************************************************************/
INVALID(IsDifferent_v<1, 1, 1, 1, 2>);
VALID(IsDifferent<1, 2, 2, 3, 4>::value);
VALID(IsDifferent_v<1, 1.0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif