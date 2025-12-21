// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_NO_LESS_THAN_H
#define CONCEPTRODON_VARYBIVORE_NO_LESS_THAN_H

#include "conceptrodon/metafunctions/varybivore/concepts/less_than.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept NoLessThan
=   LessThan<RightSide, LeftSide>
||  EqualTo<LeftSide, RightSide>;

}}

#endif