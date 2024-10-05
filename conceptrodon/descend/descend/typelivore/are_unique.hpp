// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ARE_UNIQUE_H
#define CONCEPTRODON_TYPELIVORE_ARE_UNIQUE_H

#include "conceptrodon/descend/typelivore/are_overlapping.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename FirstElement, typename...RestElements>
struct AreUnique
{
    static constexpr bool value 
    {
        not std::is_same_v
        <
            typename AreOverlapping<FirstElement>::template ProtoMold<RestElements...>::type,
            void
        >
    };
};

}}

#endif