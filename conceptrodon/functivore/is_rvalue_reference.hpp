// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_IS_RVALUE_REFERENCE_H
#define CONCEPTRODON_FUNCTIVORE_IS_RVALUE_REFERENCE_H

#include "conceptrodon/functivore/analyzer.hpp"




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG
#error "CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/rvalue_reference.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template <typename F>
struct IsRvalueReference
{
    static constexpr bool value
    { static_cast<bool>(CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsRvalueReference_v
{ static_cast<bool>(CONCEPTRODON_NUCLEOLUS_RVALUE_REFERENCE_FLAG & Analyzer<F>::value) };

}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/define_flags/rvalue_reference.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
