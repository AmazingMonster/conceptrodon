// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NO_GREATER_H
#define CONCEPTRODON_VARYBIVORE_NO_GREATER_H

#include "conceptrodon/descend/varybivore/concepts/less.hpp"
#include "conceptrodon/descend/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept NoGreater 
=   Less<LeftSide, RightSide>
||  Equal<LeftSide, RightSide>;

}}

#endif