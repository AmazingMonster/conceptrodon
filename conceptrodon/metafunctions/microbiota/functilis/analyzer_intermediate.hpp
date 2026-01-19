// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0


/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_H
#define CONCEPTRODON_FUNCTILIS_ANALYZER_H
/******************************************************************************************************/




/******************************************************************************************************/
#include <type_traits>
#include "conceptrodon/metafunctions/microbiota/functilis/analyzer_prototype.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FLAG_TYPE
#error "CONCEPTRODON_NUCLEOLUS_FLAG_TYPE has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/flag_type.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/function.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_POINTER_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/function_pointer.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG
#error "CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/pointer_to_member_function.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#ifdef CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG
#error "CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG has already been defined"
#endif

#include "conceptrodon/metafunctions/microbiota/nucleolus/define_flags/function_object.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
namespace Conceptrodon {
namespace Functilis {

template<typename Fn>
struct AnalyzerIntermediate: public Functilis::AnalyzerPrototype<Fn> {};

template<typename Fn>
struct AnalyzerIntermediate<Fn*>
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
struct AnalyzerIntermediate<MemFn Structure::*>
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
struct AnalyzerIntermediate<FO>
: public AnalyzerIntermediate<decltype(&FO::operator())>
{
    static constexpr CONCEPTRODON_NUCLEOLUS_FLAG_TYPE value
    {
        CONCEPTRODON_NUCLEOLUS_FUNCTION_OBJECT_FLAG |
        (
            CONCEPTRODON_NUCLEOLUS_POINTER_TO_MEMBER_FUNCTION_FLAG ^
            AnalyzerIntermediate<decltype(&FO::operator())>::value
        )
    };

    using class_type = FO;
};

}}
/******************************************************************************************************/




/******************************************************************************************************/
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/flag_type.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/function.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/function_pointer.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/pointer_to_member_function.hpp"
#include "conceptrodon/metafunctions/microbiota/nucleolus/undef_flags/function_object.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#endif
/******************************************************************************************************/
