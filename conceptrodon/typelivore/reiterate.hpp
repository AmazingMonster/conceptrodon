// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_REITERATE_H
#define CONCEPTRODON_TYPELIVORE_REITERATE_H

#include "conceptrodon/microbiota/typella/typical_reiterate.hpp"

namespace Conceptrodon {
namespace Typelivore {

using Typella::TypicalReiterate;

template<typename...Elements>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Elements...>
    ::template ProtoPage<Agreements...>
    ::type;
};

}}

#endif