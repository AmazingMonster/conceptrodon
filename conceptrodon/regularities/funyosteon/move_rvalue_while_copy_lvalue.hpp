// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNYOSTEON_MOVE_RVALUE_WHILE_COPY_LVALUE_H
#define CONCEPTRODON_FUNYOSTEON_MOVE_RVALUE_WHILE_COPY_LVALUE_H

#include "conceptrodon/concepts/mouldivore/passed.hpp"
#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Funyosteon {

template<typename Arg>
requires Mouldivore::Passed<std::is_lvalue_reference, Arg>
constexpr std::remove_cvref_t<Arg> move_rvalue_while_copy_lvalue(Arg&& arg)
{
    return static_cast<std::remove_cvref_t<Arg>>(arg);
}

template<typename Arg>
constexpr Arg&& move_rvalue_while_copy_lvalue(Arg&& arg)
{
    return static_cast<Arg&&>(arg);
}

}}
/******************************************************************************************************/

#endif