// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_FORWARD_IF_RVALUE_H
#define CONCEPTRODON_FUNCTIVORE_FORWARD_IF_RVALUE_H

#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename Target>
constexpr std::remove_cvref_t<Target> forward_if_rvalue(std::remove_cvref_t<Target> const & arg)
{
    return static_cast<std::remove_cvref_t<Target>>(arg);
}

template<typename Target>
constexpr Target&& forward_if_rvalue(std::remove_reference_t<Target>&& arg)
{
    return static_cast<Target&&>(arg);
}

}}
/******************************************************************************************************/

#endif