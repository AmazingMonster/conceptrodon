// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ANY_H

#include <concepts>
#include "conceptrodon/varybivore/any.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAny {




/******************************************************************************************************/
VALID(Any<1, 2, 3>::value);
VALID(Any_v<0, 1, 2, 3>);
INVALID(Any_v<0, nullptr>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif