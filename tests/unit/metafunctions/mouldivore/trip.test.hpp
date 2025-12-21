// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_TRIP_H

#include <utility>

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/mouldivore/trip.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestTrip {




/******************************************************************************************************/
template<auto I>
struct TesterA
{
    template<typename...Vals>
    struct ProtoMold
    {
        template<auto...Agreements>
        using Page = Vay<((I+...+Vals::value)+...+Agreements)>;

        using type = Vay<(I+...+Vals::value)>;

        static constexpr auto value
        {(I+...+Vals::value)};
    };

    
    template<typename...Vals>
    struct ProtoMold<void, Vals...>
    {
        template<auto...Agreements>
        using Page = Vay<((-I+...+Vals::value)+...+Agreements)>;

        using type = Vay<(-I+...+Vals::value)>;

        static constexpr auto value
        {(-I+...+Vals::value)};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename Vals>
struct TesterBHelper
{
    template<auto...Agreements>
    using Page = Shuttle<2*Vals::value, Agreements...>;

    using type = Vay<2*Vals::value>;

    static constexpr auto value { 2*Vals::value };

    template<typename>
    struct ProtoMold {};

    template<template<auto...> class AnotherSequence, auto...J>
    struct ProtoMold<AnotherSequence<J...>>
    {

        template<auto...Agreements>
        using Page = Shuttle<2*Vals::value + (0 +...+ J), Agreements...>;

        using type = Shuttle<2*Vals::value + (0 +...+ J)>;

        static constexpr auto value
        { 2*Vals::value + (0 +...+ J) };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<typename...Elements>
using TesterB = TesterBHelper<typename Elements::type...>;

template<typename Vals>
struct TesterCHelper
{
    template<auto...Agreements>
    using Page = Shuttle<Vals::value-1, Agreements...>;

    using type = Vay<Vals::value-1>;

    static constexpr auto value
    { Vals::value-1 };

    template<typename>
    struct ProtoMold {};

    template<template<auto...> class AnotherSequence, auto...J>
    struct ProtoMold<AnotherSequence<J...>>
    {

        template<auto...Agreements>
        using Page = Shuttle<Vals::value-1 + (0 +...+ J), Agreements...>;

        using type = Shuttle<Vals::value-1 + (0 +...+ J)>;

        static constexpr auto value { Vals::value-1 + (0 +...+ J) };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<typename...Elements>
using TesterC = TesterCHelper<typename Elements::type...>;

template<template<typename...> class P>
struct MoldVessel
{
    static constexpr auto value
    { P<Vay<11>>::value };
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Vay<2*2*2*(4+5)>

SAME_TYPE
(
    Trip<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Mold<Vay<5>>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<2 * (1 + 11 + 2 + 3 + 4), 10>

SAME_TYPE
(
    Trip<TesterA<1>::Mold>
    ::Road<TesterA<2>::Mold>
    ::Road<TesterA<3>::Mold>
    ::Road<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Commit
    ::Mold<Vay<11>>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<2 * (1 + 11 + 2 + 3 + 4) - 1 - 1, 10>

SAME_TYPE
(
    Trip<TesterA<1>::Mold>
    ::Road<TesterA<2>::Mold>
    ::Road<TesterA<3>::Mold>
    ::Road<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Mold<Vay<11>>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<2 * (-1 + 11 + 2 + 3 + 4) - 1 - 1, 10>

SAME_TYPE
(
    Trip<TesterA<1>::Mold>
    ::Road<TesterA<2>::Mold>
    ::Road<TesterA<3>::Mold>
    ::Road<TesterA<4>::Mold>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Mold<void, Vay<11>>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<2 * (((1 + 11 + 2 + 3 + 4) - 1) - 1), 10>

SAME_TYPE
(
    Trip<TesterA<1>::Mold>
    ::Road<TesterA<2>::Mold>
    ::Road<TesterA<3>::Mold>
    ::Road<TesterA<4>::Mold>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::Mold<Vay<11>>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2 * (((1 + 11 + 2 + 3 + 4) - 1) - 1)

EQUAL_VALUE
(
    Trip<TesterA<1>::Mold>
    ::Road<TesterA<2>::Mold>
    ::Road<TesterA<3>::Mold>
    ::Road<TesterA<4>::Mold>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::UniFlow<MoldVessel>
    ::value
);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif