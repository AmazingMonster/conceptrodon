// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VOIDIFY_H
#define CONCEPTRODON_VOIDIFY_H

namespace Conceptrodon {

template<auto...>
using Voidify = void;
 
}

#endif