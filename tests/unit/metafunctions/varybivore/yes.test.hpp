// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_YES_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_YES_H

#include "conceptrodon/metafunctions/varybivore/yes.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestYes {




/******************************************************************************************************/
static_assert(Yes<0, std::integral_constant<int, 0>{}>::value);
/******************************************************************************************************/




}}}}

#endif