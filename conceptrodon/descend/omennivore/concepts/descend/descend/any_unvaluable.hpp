// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNVALUABLE_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNVALUABLE_H

#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unvaluable.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyUnvaluable
= (...||(not Valuable<Structures>));

template<typename...Structures>
concept AnyUnvaluable
=   JustAnyUnvaluable<Structures...>
||  AllUnvaluable<Structures...>;

}}

#endif