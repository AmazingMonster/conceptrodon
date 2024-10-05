// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_TRAVEL_H
#define CONCEPTRODON_MOULDIVORE_TEST_TRAVEL_H

#include <type_traits>
#include <utility>
#include "conceptrodon/descend/mouldivore/travel.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestTravel {




/******************************************************************************************************/
template<typename...Elements>
struct TesterA
{ 
    using type = std::tuple<Elements*...>;
};

template<typename...Elements>
requires (...&&Omennivore::Valuable<Elements>)
struct TesterA<Elements...>
{ 
    using type = Shuttle<Elements::value...>;
};

template<auto...Variables>
struct TesterB
{
    using type = Shuttle<Variables+1 ...>;
};

template<typename...Elements>
struct TesterC
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
struct TesterD
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
struct TesterE
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
struct TesterF
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
    std::tuple<int***, int***, int***>

SAME_TYPE
(
    Travel<TesterA>
    ::Road<TesterA>
    ::Road<TesterA>
    ::Mold<int, int, int>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<2, 2, 2>

SAME_TYPE
(
    Travel<TesterA>
    ::Rail<TesterB>
    ::Rail<TesterB>
    ::Mold<std::integral_constant<int, 0>, std::integral_constant<int, 0>, std::integral_constant<int, 0>>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<std::tuple<int**, float, double>, std::tuple<int**, float, double>, std::tuple<int**, float, double>>

SAME_TYPE
(
    Travel<TesterA>
    ::Road<TesterA>
    ::Road<TesterC>
    ::Flow<TesterD>
    ::Mold<int, int, int>
    ::Mold<float, double>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<Shuttle<1, 10, 11>, Shuttle<1, 10, 11>, Shuttle<1, 10, 11>>

SAME_TYPE
(
    Travel<TesterA>
    ::Rail<TesterB>
    ::Rail<TesterE>
    ::Sail<TesterF>
    ::Mold<std::integral_constant<int, 0>, std::integral_constant<int, 0>, std::integral_constant<int, 0>>
    ::Page<10, 11>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif