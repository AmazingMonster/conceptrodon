// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_IS_DIFFERENT_FROM_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_IS_DIFFERENT_FROM_H

#include "conceptrodon/metafunctions/varybivore/is_different_from.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsDifferent {




/******************************************************************************************************/
INVALID(IsDifferentFrom<1>::Page_v<1>);
VALID(IsDifferentFrom<1>::Page<2>::value);
VALID(IsDifferentFrom<1>::Page_v<1.0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif