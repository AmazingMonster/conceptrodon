// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_POP_H
#define CONCEPTRODON_TYPELIVORE_POP_H

#include "conceptrodon/microbiota/typella/typical_pop.hpp"

namespace Conceptrodon {
namespace Typelivore {

using Typella::TypicalPop;

template<typename...Args>
using Pop = TypicalPop<Args...>::type;

}}

#endif