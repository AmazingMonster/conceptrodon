// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ALL_ZERO_H
#define CONCEPTRODON_VARYBIVORE_ALL_ZERO_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Args>
concept AllZero = (...&&(Args == 0));

}}

#endif