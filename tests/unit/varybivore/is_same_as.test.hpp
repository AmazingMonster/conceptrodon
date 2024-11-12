// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_AS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_AS_H

#include <concepts>
#include "conceptrodon/varybivore/is_same_as.hpp"
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
INVALID(IsSameAs<1>::Page_v<static_cast<size_t>(1)>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif