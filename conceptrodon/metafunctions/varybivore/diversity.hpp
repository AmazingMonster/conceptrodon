// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DIVERSITY_H
#define CONCEPTRODON_VARYBIVORE_DIVERSITY_H

#include "conceptrodon/metafunctions/varybivore/typical_diversity.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Diversity
{
    template<auto...Agreements>
    using Page = TypicalDiversity<Variables...>
    ::template ProtoPage<Agreements...>
    ::type;
};

}}

#endif