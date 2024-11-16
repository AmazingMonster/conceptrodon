// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_EQUAL_H
#define CONCEPTRODON_VARYBIVORE_EQUAL_H

#include "conceptrodon/varybivore/is_less.hpp"
#include "conceptrodon/varybivore/concepts/falsify.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Equal 
=   Falsify<IsLess, LeftSide, RightSide>
&&  Falsify<IsLess, RightSide, LeftSide>;

}}

#endif