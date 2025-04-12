// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_IS_FUNCTION_POINTER_H
#define CONCEPTRODON_FUNCTIVORE_IS_FUNCTION_POINTER_H

#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename>
struct IsFunctionPointer
{
    static constexpr bool value {false};
};

template<typename FP>
struct IsFunctionPointer<FP*>
{
    static constexpr bool value
    {std::is_function_v<FP>};
};

template<typename FP>
constexpr bool IsFunctionPointer_v
{
    IsFunctionPointer<FP>::value
};

}}
/******************************************************************************************************/

#endif