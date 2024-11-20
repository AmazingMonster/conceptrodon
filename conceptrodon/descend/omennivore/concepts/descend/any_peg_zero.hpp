// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PEG_ZERO_H
#define CONCEPTRODON_OMENNIVORE_ANY_PEG_ZERO_H

#include "conceptrodon/descend/omennivore/concepts/all_pegful.hpp"
#include "conceptrodon/varybivore/concepts/descend/any_zero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyPegZero
=   AllPegful<Args...>
&&  Varybivore::AnyZero<Args::value...>;

}}

#endif