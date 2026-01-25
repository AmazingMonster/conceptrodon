// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_TRUE_PROBE_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_TRUE_PROBE_H

#include "conceptrodon/concepts/varybivore/true_probe.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestTrueProbe {




/******************************************************************************************************/
static_assert(not TrueProbe<0>);
static_assert(not TrueProbe<false>);
static_assert(TrueProbe<1>);
static_assert(TrueProbe<2>);
static_assert(TrueProbe<true>);
/******************************************************************************************************/




}}}}

#endif