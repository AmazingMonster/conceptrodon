// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ALL_PASSED_H
#define CONCEPTRODON_VARYBIVORE_ALL_PASSED_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Predicate, auto...Variables>
concept AllPassed = (...&& static_cast<bool>(Predicate(Variables)));

}}

#endif