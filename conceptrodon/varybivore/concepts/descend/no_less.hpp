// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NO_LESS_H
#define CONCEPTRODON_VARYBIVORE_NO_LESS_H

#include "conceptrodon/varybivore/concepts/less.hpp"
#include "conceptrodon/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept NoLess 
=   Less<RightSide, LeftSide>
||  Equal<LeftSide, RightSide>;

}}

#endif