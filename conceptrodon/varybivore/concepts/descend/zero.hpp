// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ZERO_H
#define CONCEPTRODON_VARYBIVORE_ZERO_H

#include "conceptrodon/varybivore/concepts/equal.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto Arg>
concept Zero = Equal<Arg, 0>;

}}

#endif