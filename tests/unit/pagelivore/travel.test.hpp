// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TRAVEL_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TRAVEL_H

#include <type_traits>
#include <utility>
#include "conceptrodon/descend/pagelivore/travel.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestTravel {




/******************************************************************************************************/
template<auto...Variables>
struct TesterA
{ 
    using type = std::tuple<decltype(Variables)*...>;
};

template<auto...Variables>
requires (...&&std::is_integral_v<decltype(Variables)>)
struct TesterA<Variables...>
{ 
    using type = Shuttle<Variables+1 ...>;
};

template<auto...Variables>
struct TesterB
{
    using type = std::tuple<std::integral_constant<int, Variables+1> ...>;
};

template<typename...Elements>
struct TesterC
{
    using type = std::tuple<std::integral_constant<int, Elements::value+1> ...>;
};

template<typename...Elements>
struct TesterD
{ 
    template<typename Element>
    struct Detail
    {
        template<typename...Types>
        struct Hidden
        {using type = std::tuple<Element, Types...>;};
        
    };

    using type = Reverie<Detail<Elements>::template Hidden...>;
};

template<template<typename...> class...Containers>
struct TesterE
{ 
    template<typename...Elements>
    struct ProtoMold
    {
        using type = std::tuple<typename Containers<Elements...>::type...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<auto...Variables>
struct TesterF
{ 
    template<auto Variable>
    struct Detail
    {
        template<auto...I>
        struct Hidden
        {using type = Shuttle<Variable, I...>;};
        
    };

    using type = Phantom<Detail<Variables>::template Hidden...>;
};

template<template<auto...> class...Sequences>
struct TesterG
{ 
    template<auto...Variables>
    struct ProtoPage
    {
        using type = std::tuple<typename Sequences<Variables...>::type...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<3, 3, 3>

SAME_TYPE
(
    Travel<TesterA>
    ::Rail<TesterA>
    ::Rail<TesterA>
    ::Page<0, 0, 0>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<std::integral_constant<int, 3>, std::integral_constant<int, 3>, std::integral_constant<int, 3>>

SAME_TYPE
(
    Travel<TesterA>
    ::Rail<TesterB>
    ::Road<TesterC>
    ::Page<0, 0, 0>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple  \
    <   \
        std::tuple<std::integral_constant<int, 3>, float, double>,  \
        std::tuple<std::integral_constant<int, 3>, float, double>,  \
        std::tuple<std::integral_constant<int, 3>, float, double>   \
    >

SAME_TYPE
(
    Travel<TesterA>
    ::Rail<TesterB>
    ::Road<TesterC>
    ::Road<TesterD>
    ::Flow<TesterE>
    ::Page<0, 0, 0>
    ::Mold<float, double>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple  \
    <   \
        Shuttle<3, 10, 11>, \
        Shuttle<3, 10, 11>, \
        Shuttle<3, 10, 11>  \
    >

SAME_TYPE
(
    Travel<TesterA>
    ::Rail<TesterA>
    ::Rail<TesterA>
    ::Rail<TesterF>
    ::Sail<TesterG>
    ::Page<0, 0, 0>
    ::Page<10, 11>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif