// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NONZERO_H
#define CONCEPTRODON_VARYBIVORE_NONZERO_H

#include "conceptrodon/metafunctions/varybivore/concepts/unequal_to.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Arg>
concept Nonzero = UnequalTo<Arg, 0>;

}}

#endif