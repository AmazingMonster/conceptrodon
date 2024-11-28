// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_NOT_NEGATIVE_ONE_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/varybivore/concepts/descend/unequal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustNotNegativeOne = Varybivore::UnequalTo<Arg::value, -1>;

template<typename Arg>
concept NotNegativeOne
=   Omennivore::Valuable<Arg>
&&  JustNotNegativeOne<Arg>;

}}

#endif