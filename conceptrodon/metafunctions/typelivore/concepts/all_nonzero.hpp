// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_ALL_NONZERO_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/all_nonzero.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAllNonzero = Varybivore::AllNonzero<Args::value...>;

template<typename...Args>
concept AllNonzero
=   Omennivore::AllValuable<Args...>
&&  JustAllNonzero<Args...>;

}}

#endif