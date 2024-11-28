// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_CLARIFY_H
#define CONCEPTRODON_TYPELIVORE_ALL_CLARIFY_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Predicate, auto...Variables>
concept AllClarify = (...&&Predicate{}(Variables));

}}

#endif