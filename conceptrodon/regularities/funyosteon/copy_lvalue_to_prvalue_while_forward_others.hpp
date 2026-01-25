// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNYOSTEON_COPY_LVALUE_TO_PRVALUE_WHILE_FORWARD_OTHERS_H
#define CONCEPTRODON_FUNYOSTEON_COPY_LVALUE_TO_PRVALUE_WHILE_FORWARD_OTHERS_H

#include "conceptrodon/concepts/mouldivore/failed.hpp"
#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Funyosteon {

    template<typename Target>
    constexpr decltype(auto) copy_lvalue_to_prvalue_while_forward_others(std::remove_reference_t<Target>& arg)
    {
        if constexpr (Mouldivore::Failed<std::is_reference, Target>)
        {
            return static_cast<std::remove_cvref_t<Target>>(arg);
        }

        else
        {
            return static_cast<Target&&>(arg);
        }
    }

    template<typename Target>
    requires Mouldivore::Failed<std::is_lvalue_reference, Target>
    constexpr decltype(auto) copy_lvalue_to_prvalue_while_forward_others(std::remove_reference_t<Target>&& arg)
    {
        return static_cast<Target&&>(arg);
    }
}}
/******************************************************************************************************/

#endif