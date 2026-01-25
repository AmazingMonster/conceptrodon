// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_TRUE_PROBE_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_TRUE_PROBE_H

#include "conceptrodon/concepts/typelivore/true_probe.hpp"
#include "conceptrodon/utilities/vay.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestTrueProbe {




/******************************************************************************************************/
static_assert(not TrueProbe<Vay<0>>);
static_assert(not TrueProbe<Vay<false>>);
static_assert(TrueProbe<Vay<1>>);
static_assert(TrueProbe<Vay<2>>);
static_assert(TrueProbe<Vay<true>>);
/******************************************************************************************************/




}}}}

#endif