// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_IS_NOEXCEPT_H
#define CONCEPTRODON_FUNCTIVORE_IS_NOEXCEPT_H

#include "conceptrodon/functivore/analyzer.hpp"




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG
#error "CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/noexcept.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template <typename F>
struct IsNoexcept
{
    static constexpr bool value
    { static_cast<bool>(CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsNoexcept_v
{ static_cast<bool>(CONCEPTRODON_NUCLEOLUS_NOEXCEPT_FLAG & Analyzer<F>::value) };

}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/define_flags/noexcept.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
