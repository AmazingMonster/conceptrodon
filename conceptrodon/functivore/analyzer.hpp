// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ANALYZER_H
#define CONCEPTRODON_FUNCTIVORE_ANALYZER_H

#include "conceptrodon/microbiota/functilis/analyzer_prototype.hpp"




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FLAG_TYPE
#error "CONCEPTRODON_NUCLEOLUS_FLAG_TYPE has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/flag_type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/function.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/function_pointer.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
#error "CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/pointer_to_member_function.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG has already been defined"
#endif

#include "conceptrodon/microbiota/nucleolus/define_flags/function_object.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename Fn>
struct Analyzer: public Functilis::AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public Functilis::AnalyzerPrototype<Fn>
{
    static constexpr CONCEPTRODON_NUCLEOLUS_FLAG_TYPE value
    {
        CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG |
        (
            CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG ^
            Functilis::AnalyzerPrototype<Fn>::value
        )
    };
};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public Functilis::AnalyzerPrototype<MemFn>
{
    static constexpr CONCEPTRODON_NUCLEOLUS_FLAG_TYPE value
    {
        CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG |
        (
            CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG ^
            Functilis::AnalyzerPrototype<MemFn>::value
        )
    };

    using class_type = Structure;
};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())>
{
    static constexpr CONCEPTRODON_NUCLEOLUS_FLAG_TYPE value
    {
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG |
        (
            CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG ^
            Analyzer<decltype(&FO::operator())>::value
        )
    };

    using class_type = FO;
};

}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/microbiota/nucleolus/undef_flags/flag_type.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_flags/function.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_flags/function_pointer.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_flags/pointer_to_member_function.hpp"
#include "conceptrodon/microbiota/nucleolus/undef_flags/function_object.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
