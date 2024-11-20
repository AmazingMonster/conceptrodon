// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_GREATER_H
#define CONCEPTRODON_VARYBIVORE_GREATER_H

#include "conceptrodon/varybivore/concepts/less.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Greater = Less<RightSide, LeftSide>;

}}

#endif