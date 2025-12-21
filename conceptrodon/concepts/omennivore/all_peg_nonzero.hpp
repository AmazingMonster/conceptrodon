// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_PEG_NONZERO_H
#define CONCEPTRODON_OMENNIVORE_ALL_PEG_NONZERO_H

#include "conceptrodon/concepts/omennivore/all_pegful.hpp"
#include "conceptrodon/concepts/varybivore/all_nonzero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AllPegNonzero
=   AllPegful<Args...>
&&  Varybivore::AllNonzero<Args::value...>;

}}

#endif