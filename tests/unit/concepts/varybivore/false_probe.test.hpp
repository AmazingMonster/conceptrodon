// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_FALSE_PROBE_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_FALSE_PROBE_H

#include "conceptrodon/concepts/varybivore/false_probe.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestFalseProbe {




/******************************************************************************************************/
static_assert(FalseProbe<0>);
static_assert(FalseProbe<false>);
static_assert(not FalseProbe<1>);
static_assert(not FalseProbe<2>);
static_assert(not FalseProbe<true>);
/******************************************************************************************************/




}}}}

#endif