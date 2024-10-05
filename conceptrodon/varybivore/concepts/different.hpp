// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_DIFFERENT_H

#include "conceptrodon/varybivore/is_same.hpp"

namespace Conceptrodon {

namespace Varbola {
    
template<auto LeftSide, auto RightSide>
concept PseudoDifferent 
= not Varybivore::IsSame<LeftSide, RightSide>::value;

}

namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Different 
=   Varbola::PseudoDifferent<LeftSide, RightSide>
&&  Varbola::PseudoDifferent<RightSide, LeftSide>;

}}

#endif