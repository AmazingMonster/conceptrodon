// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SET_CONTAINS_H
#define CONCEPTRODON_TYPELIVORE_SET_CONTAINS_H

#include <type_traits>
#include "conceptrodon/utilities/tyy.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SetContains
: public Tyy<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {std::is_base_of<Tyy<Inspecting>, SetContains>::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename Inspecting>
    static constexpr bool Mold_v 
    {std::is_base_of<Tyy<Inspecting>, SetContains>::value};
};

}}

#endif