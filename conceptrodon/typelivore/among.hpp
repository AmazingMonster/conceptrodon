// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_AMONG_H
#define CONCEPTRODON_TYPELIVORE_AMONG_H

#include "conceptrodon/microbiota/typella/typical_among.hpp"

namespace Conceptrodon {
namespace Typelivore {

using Typella::TypicalAmong;

template<typename...Elements>
struct Among
{
    template<auto...Agreements>
    using Page = TypicalAmong<Elements...>
    ::template Page<Agreements...>
    ::type;
};

}};

#endif