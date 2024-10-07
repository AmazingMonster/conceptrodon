// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

// Every function in the library follows the structure presented by Exemplar.
// This document will explain the library's mechanics and design decisions.

#ifndef CONCEPTRODON_EXEMPLAR_H
#define CONCEPTRODON_EXEMPLAR_H

// Define dummy placeholder tokens for readability.
#define TEMPLATE_PARAMETER_CATEGORY auto
#define TYPE int
#define VALUE true
#define CONTENTS
#define IMPLEMENTATION int

// The core idea of the library is to dissect the process of argument passing, making signatures of metafunctions predictable and better suited for composition.
// The first attempt was to deploy member structure templates to accept further arguments.

namespace Conceptrodon {
namespace FirstAttempt
{

template<TEMPLATE_PARAMETER_CATEGORY...>
struct Exemplar
{
    template<typename...Elements>
    struct Mold {};

// While this is much clearer to implement, it has one major downfall:

    template<auto...Variables>
    struct Page
    {
//      template<auto...>
//      struct Page {};    
//      using Page = IMPLEMENTATION;    /*cannot define a member with the same name as its surrounding struct*/
    };

// Assuming we are creating a function(for the sake of this example, we let the function itself take the argument for transform)\
// that transforms a variable of certain index in any given sequence, 
// it's not possible to invoke the function by Function<Transformation>::Page<Index>::Page<Arguments...>.

// Attempts have been made to resolve this issue:

    template<template<typename...> class...Warehouses>
    struct Road
    {
        struct Slash    /* Add intermediate struct */
        {
            template<template<typename...> class...>
            struct Road {};
        };

        
        template<template<auto...> class...Stockrooms>
        struct Rail: public Road<>
        {};

// Now, the example above can be written as Exemplar<>::Page<0>::Slash::Page<Arguments...>.

    };

// This doesn't solve all of our problems. If we inherit Road to a new name:

    template<template<auto...> class...Stockrooms>
    struct Rail: public Road<>
    {};

// 'Slash' that surrounds 'Road' is not needed anymore, yet we still have to go through 'Slash' to access the inherited 'Road':\
// Exemplar<>::Rail<>::Slash::Road<>.
// An intermediate structure surrounding 'Rail' is needed now. Since it is missing, we cannot access the inherited 'Rail' from Exemplar::Rail.\
// Exemplar<>::Rail<>::Rail will refer to the constructor instead.
// These behaviors are not predictable by high-level functions. Probing into arguments' inner structures is necessary before every operation.\
// This is both complicated and inefficient.
// After studying boost::mp11 and kvasir::mpl, a second approach relying on alias templates was adopted.

};

}}

// [TODO: Add more details]

namespace Conceptrodon {

template<TEMPLATE_PARAMETER_CATEGORY...>
struct Exemplar
{
    template<typename...Elements>
    struct ProtoMold {};
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<typename Element>
    using UniMold = IMPLEMENTATION;

    template<typename FirstElement, typename SecendElement>
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

    template<auto FirstVariable, auto SecendVariable>
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

    template<template<template<auto...> class...> class...Args>
    using Sail_t = Sail<Args...>::type;

    template<template<template<auto...> class...> class...Args>
    static constexpr auto Sail_v {Sail<Args...>::value};

    template<template<template<auto...> class...> class...Stockrooms>
    using SubSail = IMPLEMENTATION;




    template<template<template<template<typename...> class...> class...> class...Madness>
    struct ProtoZeal {};

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Zeal = ProtoZeal<Agreements...>;

    template<template<template<template<typename...> class...> class...> class Madness>
    using UniZeal = Madness<CONTENTS>;

    template<template<template<template<typename...> class...> class...> class...Args>
    using Zeal_t = Zeal<Args...>::type;

    template<template<template<template<typename...> class...> class...> class...Args>
    static constexpr auto Zeal_v {Zeal<Args...>::value};

    template<template<template<template<typename...> class...> class...> class...Madness>
    using SubZeal = IMPLEMENTATION;




    template<template<template<template<auto...> class...> class...> class...Craziness>
    struct ProtoZest 
    {
        struct Slash
        {
            template<template<template<template<auto...> class...> class...> class...Arguments>
            struct ProtoZest {};
        };

        template<typename...Arguments>
        using Zest = Slash::template ProtoZest<Arguments...>;

        template<auto...>
        struct ProtoPage
        {
            template<typename...Elements>
            struct ProtoMold {};

            template<typename...Agreements>
            using Mold = ProtoMold<Agreements...>;
        };
        
        template<auto...Arguments>
        using Page = ProtoPage<Arguments...>;
                
        using type = TYPE;

        static constexpr auto value {VALUE};
    
    };
    
    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Zest = ProtoZest<Agreements...>;

    template<template<template<template<auto...> class...> class...> class Craziness>
    using UniZest = Craziness<CONTENTS>;

    template<template<template<template<auto...> class...> class...> class...Args>
    using Zest_t = Zest<Args...>::type;

    template<template<template<template<auto...> class...> class...> class...Args>
    static constexpr auto Zest_v {Zest<Args...>::value};

    template<template<template<template<auto...> class...> class...> class...Craziness>
    using SubZest = IMPLEMENTATION;




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

#endif
