// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNYOSTEON_COPY_LVALUE_WHILE_FORWARD_RVALUE_H
#define CONCEPTRODON_FUNYOSTEON_COPY_LVALUE_WHILE_FORWARD_RVALUE_H

#include "conceptrodon/concepts/mouldivore/passed.hpp"
#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Funyosteon {

template<typename Target>
constexpr std::remove_cvref_t<Target> copy_lvalue_while_forward_rvalue(std::remove_reference_t<Target>& arg)
{
    if constexpr (Mouldivore::Passed<std::is_lvalue_reference, Target>)
    {
        return static_cast<std::remove_cvref_t<Target>>(arg);
    }
    else
    {
        return static_cast<Target&&>(arg);
    }
}

template<typename Target>
constexpr Target&& copy_lvalue_while_forward_rvalue(std::remove_reference_t<Target>&& arg)
{
    return static_cast<Target&&>(arg);
}

}}
/******************************************************************************************************/

#endif