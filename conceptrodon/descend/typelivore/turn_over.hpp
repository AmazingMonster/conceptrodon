// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TURNOVER_H
#define CONCEPTRODON_TYPELIVORE_TURNOVER_H

#include "conceptrodon/descend/microbiota/typella/typical_turn_over.hpp"

namespace Conceptrodon {
namespace Typelivore {

using Typella::TypicalTurnOver;

template<typename...Elements>
using TurnOver = Typella::TypicalTurnOver<Elements...>::type;

}}

#endif