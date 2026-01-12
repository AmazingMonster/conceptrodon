// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_FUNCTORIZE_H
#define CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_FUNCTORIZE_H

#include "conceptrodon/regularities/clxyosteon/functorize.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Clxyosteon {
namespace UnitTests {
namespace TestFunctorize {

static_assert(Functorize<std::true_type>{}());
static_assert(! Functorize<std::false_type>{}());

}}}}

#endif