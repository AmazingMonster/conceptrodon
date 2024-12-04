// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_GREATER_THAN_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_GREATER_THAN_H

#include "conceptrodon/varybivore/are_greater_than.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreGreaterThan {




/******************************************************************************************************/
VALID(AreGreaterThan<0>::Page_v<1, 2, 3>);
INVALID(AreGreaterThan<0>::Page_v<0, 2, 3>);
INVALID(AreGreaterThan<1>::Page_v<0, 1>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif