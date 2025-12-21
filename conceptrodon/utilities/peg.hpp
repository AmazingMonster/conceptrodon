// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PEG_H
#define CONCEPTRODON_PEG_H

#include <cstddef>
#include <type_traits>

namespace Conceptrodon {

template <std::make_signed_t<size_t> I>
struct Peg
{ static constexpr std::make_signed_t<size_t> value {I}; };
 
}

#endif