// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_NOT_NEGATIVE_ONE_H

#include "conceptrodon/varybivore/concepts/unequal_to.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Arg>
concept NotNegativeOne = UnequalTo<Arg, -1>;

}}

#endif