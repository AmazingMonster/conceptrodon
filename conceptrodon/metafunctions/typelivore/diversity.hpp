// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_DIVERSITY_H
#define CONCEPTRODON_TYPELIVORE_DIVERSITY_H

#include "conceptrodon/metafunctions/typelivore/typical_diversity.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Diversity
{
    template<typename...Agreements>
    using Mold = TypicalDiversity<Elements...>
    ::template ProtoMold<Agreements...>
    ::type;
};

}}

#endif