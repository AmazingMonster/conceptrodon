// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_NEGATIVE_ONE_H

#include "conceptrodon/concepts/varybivore/equal_to.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Arg>
concept NegativeOne = EqualTo<Arg, -1>;

}}

#endif