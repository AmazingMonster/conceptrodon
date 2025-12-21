// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ZERO_H
#define CONCEPTRODON_TYPELIVORE_ZERO_H

#include "conceptrodon/metafunctions/omennivore/concepts/valuable.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/equal_to.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename Arg>
concept JustZero = Varybivore::EqualTo<Arg::value, 0>;

template<typename Arg>
concept Zero
=   Omennivore::Valuable<Arg>
&&  JustZero<Arg>;

}}

#endif