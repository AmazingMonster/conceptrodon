// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_NEGATIVE_ONE_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustNegativeOne = Varybivore::Equal<Arg::value, -1>;

template<typename Arg>
concept NegativeOne
=   Omennivore::Valuable<Arg>
&&  JustNegativeOne<Arg>;

}}

#endif