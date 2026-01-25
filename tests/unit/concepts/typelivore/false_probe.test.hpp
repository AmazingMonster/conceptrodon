// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_FALSE_PROBE_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_FALSE_PROBE_H

#include "conceptrodon/concepts/typelivore/false_probe.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestFalseProbe {




/******************************************************************************************************/
static_assert(FalseProbe<Vay<0>>);
static_assert(FalseProbe<Vay<false>>);
static_assert(not FalseProbe<Vay<1>>);
static_assert(not FalseProbe<Vay<2>>);
static_assert(not FalseProbe<Vay<true>>);
/******************************************************************************************************/




}}}}

#endif