// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_NO_GREATER_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_NO_GREATER_H

#include "conceptrodon/varybivore/is_no_greater.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsNoGreater {




/******************************************************************************************************/
VALID(IsNoGreater_v<0, 0, 1, 2, 3>);
INVALID(IsNoGreater<1, 0, 2, 3>::value);
VALID(IsNoGreater<0, 1>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif