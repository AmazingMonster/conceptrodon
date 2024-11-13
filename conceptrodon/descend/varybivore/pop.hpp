// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_POP_H
#define CONCEPTRODON_VARYBIVORE_POP_H

#include "conceptrodon/descend/microbiota/varbola/typical_pop.hpp"

namespace Conceptrodon {
namespace Varybivore {

using Varbola::TypicalPop;

template<auto...Args>
using Pop = TypicalPop<Args...>::type;

}}

#endif