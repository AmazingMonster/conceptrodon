// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_IS_VARIADIC_H
#define CONCEPTRODON_FUNCTIVORE_IS_VARIADIC_H

#include "conceptrodon/metafunctions/functivore/analyzer.hpp"




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
#error "CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/variadic.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template <typename F>
struct IsVariadic
{
    static constexpr bool value
    { static_cast<bool>(CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsVariadic_v
{ static_cast<bool>(CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG & Analyzer<F>::value) };

}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/variadic.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
