// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNYOSTEON_MOVE_RVALUE_COPY_LVALUE_H
#define CONCEPTRODON_FUNYOSTEON_MOVE_RVALUE_COPY_LVALUE_H

#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Funyosteon {

template<typename Target>
constexpr std::remove_cvref_t<Target> move_rvalue_copy_lvalue(std::remove_cvref_t<Target> const & arg)
{
    return static_cast<std::remove_cvref_t<Target>>(arg);
}

template<typename Target>
constexpr Target&& move_rvalue_copy_lvalue(std::remove_reference_t<Target>&& arg)
{
    return static_cast<Target&&>(arg);
}

}}
/******************************************************************************************************/

#endif