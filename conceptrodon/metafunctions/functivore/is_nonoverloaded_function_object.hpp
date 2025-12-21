// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_IS_NONOVERLOADED_FUNCTION_OBJECT_H
#define CONCEPTRODON_FUNCTIVORE_IS_NONOVERLOADED_FUNCTION_OBJECT_H

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename>
struct IsNonoverloadedFunctionObject
{
    static constexpr bool value {false};
};

template<typename FO>
requires requires {&FO::operator();}
struct IsNonoverloadedFunctionObject<FO>
{
    static constexpr bool value {true};
};

template<typename FO>
constexpr bool IsNonoverloadedFunctionObject_v
{
    requires {&FO::operator();}
};

}}
/******************************************************************************************************/

#endif