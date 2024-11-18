// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NONZERO_H
#define CONCEPTRODON_VARYBIVORE_NONZERO_H

#include "conceptrodon/descend/varybivore/concepts/descend/unequal.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Arg>
concept Nonzero = Unequal<Arg, 0>;

}}

#endif