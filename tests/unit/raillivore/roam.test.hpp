// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_ROAM_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_ROAM_H

#include <concepts>
#include <type_traits>
#include <utility>
#include "conceptrodon/descend/raillivore/roam.hpp"
#include "conceptrodon/monotony.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestRoam {




/******************************************************************************************************/
template<template<auto...> class...Sequences>
struct TesterA
{ 
    using type = std::tuple<Sequences<'*'>...>;
};

template<template<auto...> class...Sequences>
requires (...&&std::same_as<Phantom<Sequences>, Phantom<Monotony>>)
struct TesterA<Sequences...>
{ 
    using type = std::tuple<Sequences<0>...>;
};

template<>
struct TesterA<Shuttle>
{ 
    using type = Shuttle<0, 0, 0>;
};

template<auto...Variables>
struct TesterB
{
    using type = Shuttle<Variables+1 ...>;
};

template<auto...Variables>
struct TesterC
{
    using type = std::tuple<std::integral_constant<int, Variables+1> ...>;
};

template<typename...Elements>
struct TesterD
{
    using type = std::tuple<std::integral_constant<int, Elements::value+1> ...>;
};

template<typename...Elements>
struct TesterE
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
struct TesterF
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
struct TesterG
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
struct TesterH
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
    Roam<TesterA>
    ::Rail<TesterB>
    ::SubRail<TesterB>
    ::SubRail<TesterB>
    ::Rail<Shuttle>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple  \
    <   \
        std::integral_constant<int, 4>, \
        std::integral_constant<int, 4>, \
        std::integral_constant<int, 4>  \
    >

SAME_TYPE
(
    Roam<TesterA>
    ::Rail<TesterB>
    ::SubRail<TesterC>
    ::Road<TesterD>
    ::Road<TesterD>
    ::Rail<Shuttle>
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
    Roam<TesterA>
    ::Rail<TesterB>
    ::SubRail<TesterC>
    ::Road<TesterD>
    ::Road<TesterE>
    ::Flow<TesterF>
    ::Rail<Shuttle>
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
    Roam<TesterA>
    ::Rail<TesterB>
    ::SubRail<TesterB>
    ::SubRail<TesterB>
    ::SubRail<TesterG>
    ::Sail<TesterH>
    ::Rail<Shuttle>
    ::Page<10, 11>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif