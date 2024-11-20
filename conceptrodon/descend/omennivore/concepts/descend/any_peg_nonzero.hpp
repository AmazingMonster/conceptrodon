// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PEG_NONZERO_H
#define CONCEPTRODON_OMENNIVORE_ANY_PEG_NONZERO_H

#include "conceptrodon/descend/omennivore/concepts/all_pegful.hpp"
#include "conceptrodon/varybivore/concepts/descend/any_nonzero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyPegNonzero
=   AllPegful<Args...>
&&  Varybivore::AnyNonzero<Args::value...>;

}}

#endif