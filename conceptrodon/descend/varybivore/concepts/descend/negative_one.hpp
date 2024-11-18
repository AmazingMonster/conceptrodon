// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_NEGATIVE_ONE_H

#include "conceptrodon/descend/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Arg>
concept NegativeOne = Equal<Arg, -1>;

}}

#endif