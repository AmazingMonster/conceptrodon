// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_APPLY_RETURN_TYPE_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_APPLY_RETURN_TYPE_H

#include "conceptrodon/metafunctions/omennivore/apply_return_type.hpp"
#include <concepts>

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestApplyReturnType {

static_assert(std::same_as<ApplyReturnType<bool>::Mold<int, double>, bool(int, double)>);

}}}}

#endif