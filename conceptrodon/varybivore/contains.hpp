// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_CONTAINS_H
#define CONCEPTRODON_VARYBIVORE_CONTAINS_H

#include "conceptrodon/varybivore/is_same.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Contains
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {(...||(IsSame<Variables, Inspecting>::value))};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto Inspecting>
    static constexpr bool Page_v 
    {(...||(IsSame<Variables, Inspecting>::value))};
};

}}

#endif