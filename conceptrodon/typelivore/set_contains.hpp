// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SET_CONTAINS_H
#define CONCEPTRODON_TYPELIVORE_SET_CONTAINS_H

#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SetContains
:public std::type_identity<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {std::is_base_of<std::type_identity<Inspecting>, SetContains>::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename Inspecting>
    static constexpr bool Mold_v 
    {std::is_base_of<std::type_identity<Inspecting>, SetContains>::value};
};

}}

#endif