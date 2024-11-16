// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNVALUABLE_H
#define CONCEPTRODON_OMENNIVORE_UNVALUABLE_H

#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Unvaluable = not Valuable<Structure>;

}}

#endif