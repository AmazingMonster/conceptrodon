// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_IS_SAME_AS_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_IS_SAME_AS_H

#include <concepts>
#include "conceptrodon/metafunctions/varybivore/is_same_as.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsSameAs {




/******************************************************************************************************/
VALID(IsSameAs<1>::Page_v<1>);
INVALID(IsSameAs<1>::Page_v<2>);
INVALID(IsSameAs<1>::Page_v<1.0>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif