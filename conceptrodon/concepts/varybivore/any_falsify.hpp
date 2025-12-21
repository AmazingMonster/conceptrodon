// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_FALSIFY_H
#define CONCEPTRODON_VARYBIVORE_ANY_FALSIFY_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate(Variables)));

}}

#endif