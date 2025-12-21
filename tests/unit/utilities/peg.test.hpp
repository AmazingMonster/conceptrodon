// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_PEG_H
#define CONCEPTRODON_UNIT_TESTS_TEST_PEG_H

#include "conceptrodon/utilities/peg.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestPeg {




/******************************************************************************************************/
static_assert(Peg<1>::value == 1);
static_assert(Peg<1>::value != 2);
static_assert(Peg<static_cast<size_t>(1)>::value == 1);
/******************************************************************************************************/




}}}

#endif