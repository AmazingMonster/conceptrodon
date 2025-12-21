// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_PEG_ZERO_H
#define CONCEPTRODON_OMENNIVORE_ALL_PEG_ZERO_H

#include "conceptrodon/concepts/omennivore/all_pegful.hpp"
#include "conceptrodon/concepts/varybivore/all_zero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AllPegZero
=   AllPegful<Args...>
&&  Varybivore::AllZero<Args::value...>;

}}

#endif