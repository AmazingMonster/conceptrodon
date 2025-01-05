// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TURN_OVER_H
#define CONCEPTRODON_VARYBIVORE_TURN_OVER_H

#include "conceptrodon/microbiota/varbola/typical_turn_over.hpp"

namespace Conceptrodon {
namespace Varybivore {

using Varbola::TypicalTurnOver;

template<auto...Variables>
using TurnOver = Varbola::TypicalTurnOver<Variables...>::type;

}}

#endif