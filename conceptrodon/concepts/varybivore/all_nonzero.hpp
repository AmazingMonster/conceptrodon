// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ALL_NONZERO_H
#define CONCEPTRODON_VARYBIVORE_ALL_NONZERO_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept AllNonzero = (...&&(Args != 0));

}}

#endif