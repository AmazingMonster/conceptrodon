// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_IS_VOLATILE_H
#define CONCEPTRODON_FUNCTIVORE_IS_VOLATILE_H

#include "conceptrodon/functivore/analyzer.hpp"




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
#error "CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/volatile.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template <typename F>
struct IsVolatile
{
    static constexpr bool value
    { static_cast<bool>(CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsVolatile_v
{ static_cast<bool>(CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG & Analyzer<F>::value) };

}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/define_flags/volatile.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
