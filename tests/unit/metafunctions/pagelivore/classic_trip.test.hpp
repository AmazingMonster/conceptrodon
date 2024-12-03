// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_CLASSIC_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_CLASSIC_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/vay.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/pagelivore/classic_trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestClassicTrip {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<auto...Agreements>
        using Page = Vay<((I+...+Variables)+...+Agreements)>;

        using type = Shuttle<I, Variables...>;

        static constexpr auto value
        {(I+...+Variables)};
    };

    
    template<auto...Variables>
    struct ProtoPage<nullptr, Variables...>
    {
        template<auto...Agreements>
        using Page = Vay<((-I+...+Variables)+...+Agreements)>;

        using type = Shuttle<-I, Variables...>;

        static constexpr auto value
        {(-I+...+Variables)};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<typename>
struct TesterB {};

template<template<auto...> class Sequence, auto...I>
struct TesterB<Sequence<I...>>
{
    template<auto...Agreements>
    using Page = Sequence<(0 +...+ (2*I)), Agreements...>;

    using type = Sequence<(0 +...+ (2*I))>;

    static constexpr auto value { (0 +...+ (2*I)) };

    template<typename>
    struct ProtoMold {};

    template<template<auto...> class AnotherSequence, auto...J>
    struct ProtoMold<AnotherSequence<J...>>
    {

        template<auto...Agreements>
        using Page = Sequence<(0 +...+ (2*I)) + (0 +...+ J), Agreements...>;

        using type = Sequence<(0 +...+ (2*I)) + (0 +...+ J)>;

        static constexpr auto value { (0 +...+ (2*I)) + (0 +...+ J) };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<typename Element>
struct TesterC {};

template<template<auto...> class Sequence, auto...I>
struct TesterC<Sequence<I...>>
{
    template<auto...Agreements>
    using Page = Sequence<(0 +...+ (I-1)), Agreements...>;

    using type = Sequence<(0 +...+ (I-1))>;

    static constexpr auto value { (0 +...+ (I-1)) };

    template<typename>
    struct ProtoMold {};

    template<template<auto...> class AnotherSequence, auto...J>
    struct ProtoMold<AnotherSequence<J...>>
    {

        template<auto...Agreements>
        using Page = Sequence<(0 +...+ (I-1)) + (0 +...+ J), Agreements...>;

        using type = Sequence<(0 +...+ (I-1)) + (0 +...+ J)>;

        static constexpr auto value { (0 +...+ (I-1)) + (0 +...+ J) };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<template<auto...> class P>
struct PageVessel
{
    static constexpr auto value
    { P<11>::value };
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<2*2*2*4 + 2*2*2*5>

SAME_TYPE
(
    ClassicTrip<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Page<5>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<(((2*1 + 2*11) + 2*2) + 2*3) + 2*4, 10>

SAME_TYPE
(
    ClassicTrip<TesterA<1>::Page>
    ::Rail<TesterA<2>::Page>
    ::Rail<TesterA<3>::Page>
    ::Rail<TesterA<4>::Page>
    ::Road<TesterB>
    ::Commit
    ::Page<11>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<((((2*1 + 2*11) + 2*2) + 2*3) + 2*4) - 1 - 1, 10>

SAME_TYPE
(
    ClassicTrip<TesterA<1>::Page>
    ::Rail<TesterA<2>::Page>
    ::Rail<TesterA<3>::Page>
    ::Rail<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Page<11>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<((((2*(-1) + 2*11) + 2*2) + 2*3) + 2*4) - 1 - 1, 10>

SAME_TYPE
(
    ClassicTrip<TesterA<1>::Page>
    ::Rail<TesterA<2>::Page>
    ::Rail<TesterA<3>::Page>
    ::Rail<TesterA<4>::Page>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Page<nullptr, 11>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<2 * ((((((1 + 11) + 2) + 3) - 1) + (4 - 1)) - 1), 10>

SAME_TYPE
(
    ClassicTrip<TesterA<1>::Page>
    ::Rail<TesterA<2>::Page>
    ::Rail<TesterA<3>::Page>
    ::Rail<TesterA<4>::Page>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::Page<11>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2 * ((((((1 + 11) + 2) + 3) - 1) + (4 - 1)) - 1)

EQUAL_VALUE
(
    ClassicTrip<TesterA<1>::Page>
    ::Rail<TesterA<2>::Page>
    ::Rail<TesterA<3>::Page>
    ::Rail<TesterA<4>::Page>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::UniSail<PageVessel>
    ::value
);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif