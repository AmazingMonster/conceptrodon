#ifndef CONCEPTRODON_MOULDIVORE_TEST_TRIP_H
#define CONCEPTRODON_MOULDIVORE_TEST_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/mouldivore/trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestTrip {




/******************************************************************************************************/
template<typename T>
struct TesterA
{ 
    using type = T*; 
    static constexpr auto value {0};
};

template<auto V>
struct TesterB
{
    static constexpr auto value {V};
    using type = TesterB;
};

template<typename T>
struct TesterC
{
    static constexpr auto value {T::value + 1};
};

template<typename T>
struct TesterD
{
    template<typename First, typename Second, typename...Ts>
    struct ProtoMold
    { using type = std::tuple<T, Second>;};

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<template<typename...> class W>
struct TesterE
{
    template<typename...Elements>
    using Mold = W<Elements...>;
};

template<auto V>
struct TesterF
{
    template<auto First, auto Second, auto...Vs>
    struct ProtoPage
    { using type = std::index_sequence<V, Second>;};

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

template<template<auto...> class S>
struct TesterG
{
    template<auto...Variables>
    using Page = S<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    int***
#define SUPPOSED_VALUE  \
    1

SAME_TYPE(Trip<TesterA>::Road<TesterA>::Road<TesterA>::Mold<int>::type);
EQUAL_VALUE(Trip<TesterA>::Road<TesterA>::Road<TesterA>::Rail<TesterB>::Road<TesterC>::Mold<std::integral_constant<int, 1>>::value);

#undef SUPPOSED_VALUE
#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterB<0>

SAME_TYPE(Trip<TesterA>::Road<TesterA>::Road<TesterA>::Rail<TesterB>::Mold<std::integral_constant<int, 1>>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<int***, float>

SAME_TYPE(Trip<TesterA>::Road<TesterA>::Road<TesterA>::Road<TesterD>::Flow<TesterE>::Mold<int>::Mold<int, float, double>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::index_sequence<1, 11>

SAME_TYPE(Trip<TesterA>::Rail<TesterB>::Road<TesterC>::Rail<TesterF>::Sail<TesterG>::Mold<int>::Page<10, 11, 12>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif