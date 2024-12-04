// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_TRIP_H

#include <utility>

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/raillivore/trip.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestTrip {




/******************************************************************************************************/
template<auto...>
struct DummySequence {};

template<auto I>
struct TesterA
{
    template<template<auto...> class Sequence>
    struct ProtoRail
    {
        template<auto...Agreements>
        using Page = Sequence<I, Agreements...>;

        using type = Sequence<I>;

        static constexpr auto value {I};
    };

    template<>
    struct ProtoRail<DummySequence>
    {
        template<auto...Agreements>
        using Page = DummySequence<-I, Agreements...>;

        using type = DummySequence<-I>;

        static constexpr auto value {-I};
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
};

template<typename>
struct TesterBHelper {};

template<template<auto...> class Sequence, auto...I>
struct TesterBHelper<Sequence<I...>>
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

template<typename...Elements>
using TesterB = TesterBHelper<typename Elements::type...>;

template<typename Element>
struct TesterCHelper {};

template<template<auto...> class Sequence, auto...I>
struct TesterCHelper<Sequence<I...>>
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

template<typename...Elements>
using TesterC = TesterCHelper<typename Elements::type...>;

template<template<template<auto...> class...> class R>
struct RailVessel
{
    static constexpr auto value
    { R<Shuttle>::value };
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<2*2*2*4>

SAME_TYPE
(
    Trip<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Commit
    ::Rail<Shuttle>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<2*4 + 2*3 + 2*2 + 2*1, 10>

SAME_TYPE
(
    Trip<TesterA<1>::Rail>
    ::Sail<TesterA<2>::Rail>
    ::Sail<TesterA<3>::Rail>
    ::Sail<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Commit
    ::Rail<Shuttle>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<2*4 + 2*3 + 2*2 + 2*1 - 1 - 1, 10>

SAME_TYPE
(
    Trip<TesterA<1>::Rail>
    ::Sail<TesterA<2>::Rail>
    ::Sail<TesterA<3>::Rail>
    ::Sail<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Rail<Shuttle>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    DummySequence<2*4 + 2*3 + 2*2 + 2*(-1) - 1 - 1, 10>

SAME_TYPE
(
    Trip<TesterA<1>::Rail>
    ::Sail<TesterA<2>::Rail>
    ::Sail<TesterA<3>::Rail>
    ::Sail<TesterA<4>::Rail>
    ::Road<TesterB>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Commit
    ::Rail<DummySequence>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE  \
    Shuttle<((4-1) + (3-1) + (2-1) + (1-1) - 1) * 2, 10>

SAME_TYPE
(
    Trip<TesterA<1>::Rail>
    ::Sail<TesterA<2>::Rail>
    ::Sail<TesterA<3>::Rail>
    ::Sail<TesterA<4>::Rail>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::Rail<Shuttle>
    ::Page<10>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    ((4-1) + (3-1) + (2-1) + (1-1) - 1) * 2


EQUAL_VALUE
(
    Trip<TesterA<1>::Rail>
    ::Sail<TesterA<2>::Rail>
    ::Sail<TesterA<3>::Rail>
    ::Sail<TesterA<4>::Rail>
    ::Road<TesterC>
    ::Road<TesterC>
    ::Road<TesterB>
    ::Commit
    ::Hail<RailVessel>
    ::value
);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif