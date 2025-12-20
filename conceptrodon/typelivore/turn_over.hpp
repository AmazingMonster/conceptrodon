// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TURNOVER_H
#define CONCEPTRODON_TYPELIVORE_TURNOVER_H

#include "conceptrodon/typelivore/typical_turn_over.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
using TurnOver = TypicalTurnOver<Elements...>::type;

}}

#endif