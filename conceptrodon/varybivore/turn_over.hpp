// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TURN_OVER_H
#define CONCEPTRODON_VARYBIVORE_TURN_OVER_H

#include "conceptrodon/varybivore/typical_turn_over.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
using TurnOver = TypicalTurnOver<Variables...>::type;

}}

#endif