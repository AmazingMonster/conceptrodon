// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_UNIQUE_H
#define CONCEPTRODON_VARYBIVORE_ARE_UNIQUE_H

#include "conceptrodon/descend/varybivore/are_overlapping.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto FirstVariable, auto...RestVariables>
struct AreUnique
{
    static constexpr bool value 
    {
        not std::is_same_v
        <
            typename AreOverlapping<FirstVariable>::template ProtoPage<RestVariables...>::type,
            void
        >
    };
};

}}

#endif