// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_MAKE_SET_H
#define CONCEPTRODON_VARYBIVORE_MAKE_SET_H

#include "conceptrodon/descend/varybivore/diversity.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto FirstVariable, auto...Variables>
struct MakeSet
{
    using type = Diversity<FirstVariable>::template ProtoPage<Variables...>
    ::type;
};

}}

#endif