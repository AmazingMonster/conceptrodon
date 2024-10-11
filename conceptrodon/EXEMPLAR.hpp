// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

// This document will explain the mechanics and design decisions of the library.

#ifndef CONCEPTRODON_EXEMPLAR_H
#define CONCEPTRODON_EXEMPLAR_H

// Define dummy placeholder tokens for readability.
#define TEMPLATE_PARAMETER_CATEGORY auto
#define TYPE int
#define VALUE true
#define CONTENTS
#define IMPLEMENTATION int
#define POSSIBLY_A_TEMPLATE

// The core idea of this library is to dissect the process of argument passing, \
// making signatures of metafunctions predictable and better suited for composition.
// The first attempt was to deploy member class templates to accept arguments of different categories.

namespace Conceptrodon {
namespace AbandonedSolution
{

POSSIBLY_A_TEMPLATE
struct Exemplar
{
    template<typename...Elements>
    struct Mold {};


// While the idea is straightforward, the implementation gets convoluted as functions become more complex.
// The main issue with this approach is that defining a member with the same name as its surrounding class is forbidden in C++, \
// possibly due to the name collision with the injected class name.
// For example:

    template<auto...Variables>
    struct Page
    {
//      template<auto...>
//      struct Page {}  /* Error: Member 'Page' has the same name as its class clang(member_name_of_class) */
    };

// Assuming we are creating a function that transforms the variable of at a given position in a given sequence, 
// it's impossible to invoke the function by 'Function<Transformation>:: Page<Index>:: Page<Arguments...>.'

// One solution is to add an intermediate structure between the class and its problematic member.

    template<template<typename...> class...Warehouses>
    struct Road
    {
        struct Slash    /* Add intermediate struct */
        {
            template<template<typename...> class...>
            struct Road 
            {
                static constexpr bool value {true};
            };
        };

        
        template<template<auto...> class...Stockrooms>
        struct Rail 
        {
            static constexpr bool value {true};
        };

// Recall the function we wanted to create earlier. 
// The following invoke sequence is possible: 'Function<Transformation>:: Page<Index>:: Slash:: Page<Arguments...>.'

    };

// However, this creates another problem. If we inherit Road to a new name:

    template<template<auto...> class...Stockrooms>
    struct Rail: public Road<>
    {};

// Since the name of the surrounding class changes to 'Rail,' \
// the intermediate structure that surrounds 'Road' is unnecessary, \
// yet we still have to go through 'Slash' to access the inherited 'Road': 

    static_assert(Rail<>:: Slash:: Road<>::value);

// Since 'Road<>:: Rail' has the same name as the new surrounding class, an intermediate structure is needed.
// We cannot access the inherited 'Rail' from Exemplar:: Rail, \
// as 'Rail<>:: Rail' will refer to the constructor instead.

//  static_assert(Rail<>:: Rail<>::value); /* Error */

// These behaviors are not predictable by high-level functions.
// Probing into arguments' inner structures is necessary before every operation, which is complicated and inefficient.

// The library was first written using this method.
// Convoluted machineries were used to remove or add intermediate structures when necessary. 
// While it was doable, the added complexity was daunting and opposed to the goal of making metafunction composition simple. 
// After studying boost::mp11 and kvasir::mpl, the author adopted a second approach, \
// which uses alias templates for interface and class templates for implementation.

};

}}

namespace Conceptrodon {
namespace AdoptedSolution{

// Check out the following example:

POSSIBLY_A_TEMPLATE
struct Exemplar
{
    template<typename...Elements>
    struct ProtoMold 
    {
        struct Slash
        {
            template<typename...>
            struct ProtoMold 
            {
                struct Slash
                {
                    template<typename...>
                    struct ProtoMold 
                    {
                        static constexpr bool value {true};
                    };
                };

// We still face the issue as before. 
// Intermediate structures are necessary between layers with the same name. 
// However, since the name of an alias template won't be injected into the class it refers to, \
// we can reuse the name inside the said class:

                template<typename...Agreements>
                using Mold = Slash::template ProtoMold<Agreements...>;
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

// This means the navigation within the class can be hidden inside the interface, \
// creating a uniform call site for high-level functions:
    
    static_assert(Mold<>::Mold<>::Mold<>::value);

// However, possibly due to optimization concerns, \
// when passing arguments to an alias template, \
// pack expansion cannot be used for a non-pack parameter.

    template<auto>
    using Page = IMPLEMENTATION;

    template<auto...Variables>
    struct Detail
    {
//     using type = Page<Variables...>; /* Error */
    };

// A few alias templates with prefixed names are introduced to avoid unnecessary indirection.
// For example:

    template<typename...Elements>
    struct Hidden
    {
        template<template<typename...> class Container>
        struct Detail { using type = Container<Elements...>; };

        template<template<typename...> class...Agreements> /* Indirection needed to make 'Road' usable with pack expansion */
        using Road = Detail<Agreements...>;

        template<template<typename...> class Container>
        using UniRoad = Container<Elements...>; /* Added to avoid indirection */
    };
};

}}

// The following example shows the full layout of a general function in the library.

namespace Conceptrodon {

template<TEMPLATE_PARAMETER_CATEGORY...>
struct Exemplar
{                
    using type = TYPE;

    static constexpr auto value {VALUE};




    template<typename...Elements>
    struct ProtoMold {};
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<typename Element>
    using UniMold = IMPLEMENTATION;

    template<typename First, typename Secend>
    using DuoMold = IMPLEMENTATION;

    template<typename...Args>
    using Mold_t = Mold<Args...>::type;

    template<typename...Args>
    static constexpr auto Mold_v {Mold<Args...>::value};
    
    template<typename...Elements>
    using SubMold = IMPLEMENTATION;




    template<auto...Variables>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto Variable>
    using UniPage = IMPLEMENTATION;

    template<auto First, auto Secend>
    using DuoPage = IMPLEMENTATION;

    template<auto...Args>
    using Page_t = Page<Args...>::type;

    template<auto...Args>
    static constexpr auto Page_v {Page<Args...>::value};

    template<auto...Variables>
    using SubPage = IMPLEMENTATION;




    template<template<typename...> class...Containers>
    struct ProtoRoad {};

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class Container>
    using UniRoad = Container<CONTENTS>;

    template<template<typename...> class First, template<typename...> class Second>
    using DuoRoad = IMPLEMENTATION;

    template<template<typename...> class...Args>
    using Road_t = Road<Args...>::type;

    template<template<typename...> class...Args>
    static constexpr auto Road_v {Road<Args...>::value};

    template<template<typename...> class...Containers>
    using SubRoad = IMPLEMENTATION;
    



    template<template<auto...> class...Sequences>
    struct ProtoRail {};

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class Sequence>
    using UniRail = Sequence<CONTENTS>;

    template<template<auto...> class First, template<auto...> class Second>
    using DuoRail = IMPLEMENTATION;

    template<template<auto...> class...Args>
    using Rail_t = Rail<Args...>::type;

    template<template<auto...> class...Args>
    static constexpr auto Rail_v {Rail<Args...>::value};

    template<template<auto...> class...Sequences>
    using SubRail = IMPLEMENTATION;
    



    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow {};

    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;

    template<template<template<typename...> class...> class Warehouse>
    using UniFlow = Warehouse<CONTENTS>;

    template<template<template<typename...> class...> class First, template<template<typename...> class...> class Second>
    using DuoFlow = IMPLEMENTATION;

    template<template<template<typename...> class...> class...Args>
    using Flow_t = Flow<Args...>::type;

    template<template<template<typename...> class...> class...Args>
    static constexpr auto Flow_v {Flow<Args...>::value};

    template<template<template<typename...> class...> class...Warehouses>
    using SubFlow = IMPLEMENTATION;




    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail {};
    
    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;

    template<template<template<auto...> class...> class Stockroom>
    using UniSail = Stockroom<CONTENTS>;

    template<template<template<auto...> class...> class First, template<template<auto...> class...> class Second>
    using DuoSail = IMPLEMENTATION;

    template<template<template<auto...> class...> class...Args>
    using Sail_t = Sail<Args...>::type;

    template<template<template<auto...> class...> class...Args>
    static constexpr auto Sail_v {Sail<Args...>::value};

    template<template<template<auto...> class...> class...Stockrooms>
    using SubSail = IMPLEMENTATION;




    template<template<template<template<typename...> class...> class...> class...Sorrow>
    struct ProtoSnow {};

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;

    template<template<template<template<typename...> class...> class...> class Sorrow>
    using UniSnow = Sorrow<CONTENTS>;

    template
    <
        template<template<template<typename...> class...> class...> class First, 
        template<template<template<typename...> class...> class...> class Second
    >
    using DuoSnow = IMPLEMENTATION;

    template<template<template<template<typename...> class...> class...> class...Args>
    using Snow_t = Snow<Args...>::type;

    template<template<template<template<typename...> class...> class...> class...Args>
    static constexpr auto Snow_v {Snow<Args...>::value};

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using SubSnow = IMPLEMENTATION;




    template<template<template<template<auto...> class...> class...> class...Melancholy>
    struct ProtoHail {};
    
    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;

    template<template<template<template<auto...> class...> class...> class Melancholy>
    using UniHail = Melancholy<CONTENTS>;

    template
    <
        template<template<template<auto...> class...> class...> class First, 
        template<template<template<auto...> class...> class...> class Second
    >
    using DuoHail = IMPLEMENTATION;

    template<template<template<template<auto...> class...> class...> class...Args>
    using Hail_t = Hail<Args...>::type;

    template<template<template<template<auto...> class...> class...> class...Args>
    static constexpr auto Hail_v {Hail<Args...>::value};

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using SubHail = IMPLEMENTATION;




    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    struct ProtoLull {};

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Lull = ProtoLull<Agreements...>;

    template<template<template<template<template<typename...> class...> class...> class...> class Silence>
    using UniLull = Silence<CONTENTS>;

    template
    <
        template<template<template<template<typename...> class...> class...> class...> class First, 
        template<template<template<template<typename...> class...> class...> class...> class Second
    >
    using DuoLull = IMPLEMENTATION;

    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    using Lull_t = Lull<Args...>::type;

    template<template<template<template<template<typename...> class...> class...> class...> class...Args>
    static constexpr auto Lull_v {Lull<Args...>::value};

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using SubLull = IMPLEMENTATION;




    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    struct ProtoCalm {};

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;

    template<template<template<template<template<auto...> class...> class...> class...> class Tranquil>
    using UniCalm = Tranquil<CONTENTS>;

    template
    <
        template<template<template<template<auto...> class...> class...> class...> class First, 
        template<template<template<template<auto...> class...> class...> class...> class Second
    >
    using DuoCalm = IMPLEMENTATION;

    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    using Calm_t = Calm<Args...>::type;

    template<template<template<template<template<auto...> class...> class...> class...> class...Args>
    static constexpr auto Calm_v {Calm<Args...>::value};

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using SubCalm = IMPLEMENTATION;




    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoHope {};

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Hope = ProtoHope<Agreements...>;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine>
    using UniHope = Sunshine<CONTENTS>;

    template
    <
        template<template<template<template<template<typename...> class...> class...> class...> class...> class First, 
        template<template<template<template<template<typename...> class...> class...> class...> class...> class Second
    >
    using DuoHope = IMPLEMENTATION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    using Hope_t = Hope<Args...>::type;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Args>
    static constexpr auto Hope_v {Hope<Args...>::value};

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines>
    using SubHope = IMPLEMENTATION;




    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoWill {};

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Sunshine>
    using UniWill = Sunshine<CONTENTS>;

    template
    <
        template<template<template<template<template<auto...> class...> class...> class...> class...> class First, 
        template<template<template<template<template<auto...> class...> class...> class...> class...> class Second
    >
    using DuoWill = IMPLEMENTATION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    using Will_t = Will<Args...>::type;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    static constexpr auto Will_v {Will<Args...>::value};

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines>
    using SubWill = IMPLEMENTATION;




    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoGlow {};

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine>
    using UniGlow = Sunshine<CONTENTS>;

    template
    <
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class First, 
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Second
    >
    using DuoGlow = IMPLEMENTATION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    using Glow_t = Glow<Args...>::type;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Args>
    static constexpr auto Glow_v {Glow<Args...>::value};

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using SubGlow = IMPLEMENTATION;




    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoDawn {};

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine>
    using UniDawn = Sunshine<CONTENTS>;

    template
    <
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class First, 
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Second
    >
    using DuoDawn = IMPLEMENTATION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    using Dawn_t = Dawn<Args...>::type;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Args>
    static constexpr auto Dawn_v {Dawn<Args...>::value};

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using SubDawn = IMPLEMENTATION;




    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto idyl(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto lark(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto ease(...) {};
    
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto free(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto glee(...) {};

    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto glad(...) {};
    
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto rosy(...) {};
    
    template<TEMPLATE_PARAMETER_CATEGORY...>
    static consteval auto rapt(...) {};




    template<TEMPLATE_PARAMETER_CATEGORY...>
    struct Detail 
    {
        template<TEMPLATE_PARAMETER_CATEGORY...>
        struct Hidden 
        {
            template<TEMPLATE_PARAMETER_CATEGORY...>
            struct Secret 
            {
                template<TEMPLATE_PARAMETER_CATEGORY...>
                struct Covert 
                {
                    template<TEMPLATE_PARAMETER_CATEGORY...>
                    struct Veiled 
                    {
                        template<TEMPLATE_PARAMETER_CATEGORY...>
                        struct Trivia
                        {
                            template<TEMPLATE_PARAMETER_CATEGORY...>
                            struct Unsaid
                            {
                                template<TEMPLATE_PARAMETER_CATEGORY...>
                                struct Untold {};
                            };
                        };
                    };
                };
            };
        };
    };
};

}

#undef TEMPLATE_PARAMETER_CATEGORY
#undef TYPE
#undef VALUE
#undef CONTENTS
#undef IMPLEMENTATION
#undef POSSIBLY_A_TEMPLATE

#endif
