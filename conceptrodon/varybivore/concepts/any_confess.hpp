// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_CONFESS_H
#define CONCEPTRODON_VARYBIVORE_ANY_CONFESS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Predicate, typename...Elements>
concept AnyConfess = (...||Predicate(Elements::value));

}}

#endif