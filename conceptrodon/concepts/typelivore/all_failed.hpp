// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ALL_FAILED_H
#define CONCEPTRODON_TYPELIVORE_ALL_FAILED_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Predicate, auto...Variables>
concept AllFailed = (...&&(not Predicate{}(Variables)));

}}

#endif