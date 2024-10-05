// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SAME_H
#define CONCEPTRODON_VARYBIVORE_SAME_H

#include "conceptrodon/varybivore/is_same.hpp"

namespace Conceptrodon {

namespace Varbola {
    
template<auto LeftSide, auto RightSide>
concept PseudoSame 
= Varybivore::IsSame<LeftSide, RightSide>::value;

}

namespace Varybivore {

template<auto LeftSide, auto RightSide>
concept Same
=   Varbola::PseudoSame<LeftSide, RightSide>
&&  Varbola::PseudoSame<RightSide, LeftSide>;

}}

#endif