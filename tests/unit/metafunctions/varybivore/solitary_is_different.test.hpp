// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SOLITARY_IS_DIFFERENT_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SOLITARY_IS_DIFFERENT_H

#include "conceptrodon/varybivore/solitary_is_different.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestSolitaryIsDifferent {




/******************************************************************************************************/
INVALID(SolitaryIsDifferent_v<1, 1>);
VALID(SolitaryIsDifferent<1, 2>::value);
VALID(SolitaryIsDifferent_v<1, 1.0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif