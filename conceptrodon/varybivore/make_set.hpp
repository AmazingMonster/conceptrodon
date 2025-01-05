// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_MAKE_SET_H
#define CONCEPTRODON_VARYBIVORE_MAKE_SET_H

#include "conceptrodon/varybivore/diversity.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
using MakeSet = TypicalDiversity<>
::ProtoPage<Variables...>
::type;

}}

#endif