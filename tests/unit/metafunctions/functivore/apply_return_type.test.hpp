// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_APPLY_RETURN_TYPE_H
#define CONCEPTRODON_TESTS_UNIT_FUNCTIVORE_APPLY_RETURN_TYPE_H

#include "conceptrodon/metafunctions/functivore/apply_return_type.hpp"
#include <concepts>

namespace Conceptrodon {
namespace Functivore {
namespace UnitTests {
namespace TestApplyReturnType {

static_assert(std::same_as<ApplyReturnType<bool>::Mold<int, double>, bool(int, double)>);

}}}}

#endif