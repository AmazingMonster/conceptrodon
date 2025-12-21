// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_CONFESS_H
#define CONCEPTRODON_TYPELIVORE_CONFESS_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Predicate, typename...Elements>
concept Confess = Predicate{}(Elements::value...);

}}

#endif