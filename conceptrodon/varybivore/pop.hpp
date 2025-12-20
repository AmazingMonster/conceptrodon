// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_POP_H
#define CONCEPTRODON_VARYBIVORE_POP_H

#include "conceptrodon/varybivore/typical_pop.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
using Pop = TypicalPop<Args...>::type;

}}

#endif