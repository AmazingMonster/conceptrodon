// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_YES_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_YES_H

#include "conceptrodon/metafunctions/typelivore/yes.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestYes {




/******************************************************************************************************/
static_assert(Yes<int, std::type_identity<int>>::value);
/******************************************************************************************************/




}}}}

#endif