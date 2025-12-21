// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNVALUABLE_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNVALUABLE_H

#include "conceptrodon/metafunctions/omennivore/concepts/unvaluable.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/all_unvaluable.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyUnvaluable
= (...||(Unvaluable<Structures>));

template<typename...Structures>
concept AnyUnvaluable
=   JustAnyUnvaluable<Structures...>
||  AllUnvaluable<Structures...>;

}}

#endif