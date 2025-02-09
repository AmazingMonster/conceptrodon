// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_CLARIFY_H
#define CONCEPTRODON_VARYBIVORE_ANY_CLARIFY_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Predicate, auto...Variables>
concept AnyClarify = (...||(Predicate(Variables)));

}}

#endif