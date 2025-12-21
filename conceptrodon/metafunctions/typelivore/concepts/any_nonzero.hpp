// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_NONZERO_H
#define CONCEPTRODON_TYPELIVORE_ANY_NONZERO_H

#include "conceptrodon/metafunctions/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/any_nonzero.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Args>
concept JustAnyNonzero = Varybivore::AnyNonzero<Args::value...>;

template<typename...Args>
concept AnyNonzero
=   Omennivore::AllValuable<Args...>
&&  JustAnyNonzero<Args...>;

}}

#endif