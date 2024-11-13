// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_REITERATE_H
#define CONCEPTRODON_VARYBIVORE_REITERATE_H

#include "conceptrodon/descend/microbiota/varbola/typical_reiterate.hpp"

namespace Conceptrodon {
namespace Varybivore {

using Varbola::TypicalReiterate;

template<auto...Variables>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Variables...>
    ::template ProtoPage<Agreements...>
    ::type;
};

}}

#endif