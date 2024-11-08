// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_MAKE_SET_H
#define CONCEPTRODON_TYPELIVORE_MAKE_SET_H

#include "conceptrodon/descend/typelivore/typical_diversity.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
using MakeSet = TypicalDiversity<>
::ProtoMold<Elements...>
::type;

}}

#endif