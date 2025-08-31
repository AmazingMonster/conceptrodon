// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PEG_H
#define CONCEPTRODON_PEG_H

#include <cstddef>

namespace Conceptrodon {

template <size_t I>
struct Peg
{ static constexpr size_t value {I}; };
 
}

#endif