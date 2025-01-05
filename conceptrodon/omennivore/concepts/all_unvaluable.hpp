// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_UNVALUABLE_H
#define CONCEPTRODON_OMENNIVORE_ALL_UNVALUABLE_H

#include "conceptrodon/omennivore/concepts/unvaluable.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllUnvaluable = (...&&Unvaluable<Structures>);

}}

#endif