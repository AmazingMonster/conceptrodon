// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_BOOLEAN_H
#define CONCEPTRODON_VARYBIVORE_TEST_BOOLEAN_H

#include <concepts>
#include "conceptrodon/varybivore/boolean.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestBoolean {




/******************************************************************************************************/
VALID(Boolean_v<10>);
INVALID(Boolean_v<0>);
INVALID(Boolean_v<nullptr>);
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Boolean<1>::value);
INVALID(Boolean<0>::value);
INVALID(Boolean<nullptr>::value);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif