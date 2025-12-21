// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_NO_GREATER_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_NO_GREATER_THAN_H

#include "conceptrodon/metafunctions/varybivore/are_no_greater_than.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreNoGreaterThan {




/******************************************************************************************************/
VALID(AreNoGreaterThan<5>::Page_v<0, 1, 2>);
INVALID(AreNoGreaterThan<5>::Page_v<6, 1, 2, 3>);
VALID(AreNoGreaterThan<5>::Page<0>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif