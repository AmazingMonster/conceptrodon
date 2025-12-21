// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_NEGATIVE_ONE_H
#define CONCEPTRODON_TYPELIVORE_NEGATIVE_ONE_H

#include "conceptrodon/metafunctions/omennivore/concepts/valuable.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustNegativeOne = Varybivore::EqualTo<Arg::value, -1>;

template<typename Arg>
concept NegativeOne
=   Omennivore::Valuable<Arg>
&&  JustNegativeOne<Arg>;

}}

#endif