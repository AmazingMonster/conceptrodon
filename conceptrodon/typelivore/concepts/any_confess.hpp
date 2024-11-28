// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ANY_CONFESS_H
#define CONCEPTRODON_TYPELIVORE_ANY_CONFESS_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Predicate, typename...Elements>
concept AnyConfess = (...||Predicate{}(Elements::value));

}}

#endif