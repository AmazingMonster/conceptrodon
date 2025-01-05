// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SET_CONTAINS_H
#define CONCEPTRODON_VARYBIVORE_SET_CONTAINS_H

#include <type_traits>
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct SetContains
:public Vay<Variables>...
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {std::is_base_of<Vay<Inspecting>, SetContains>::value};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto Inspecting>
    static constexpr bool Page_v 
    {std::is_base_of<Vay<Inspecting>, SetContains>::value};
};

}}

#endif