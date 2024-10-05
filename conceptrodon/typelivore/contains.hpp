// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_CONTAINS_H
#define CONCEPTRODON_TYPELIVORE_CONTAINS_H

#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Contains
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {(...||(std::is_same_v<Elements, Inspecting>))};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename Inspecting>
    static constexpr bool Mold_v 
    {(...||(std::is_same_v<Elements, Inspecting>))};
};

}}

#endif