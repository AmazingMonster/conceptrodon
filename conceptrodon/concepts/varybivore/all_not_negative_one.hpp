// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ALL_NOT_NEGATIVE_ONE_H
#define CONCEPTRODON_VARYBIVORE_ALL_NOT_NEGATIVE_ONE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept AllNotNegativeOne = (...&&(Args != -1));

}}

#endif