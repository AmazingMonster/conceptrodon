// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TRIP_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/monotony.hpp"
#include "conceptrodon/pagelivore/trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/emissary.hpp"
#include "conceptrodon/diplomat.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestTrip {




/******************************************************************************************************/
template<auto Variable>
struct TesterA
{ 
    using type = decltype(Variable);
};

template<auto Variable>
requires std::is_integral_v<decltype(Variable)>
struct TesterA<Variable>
{ 
    using type = decltype(Variable);
    static constexpr auto value {Variable};
};

template<typename Element>
struct TesterB
{
    using type = Element*;

    template<typename, typename Target, typename...>
    struct ProtoMold
    {
        using type = std::tuple<TesterB::type, Target>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<typename Element>
requires Omennivore::Valuable<Element>
struct TesterC
{
    using type = TesterC;
    static constexpr auto value {Element::value + 1};
};

template<auto Variable>
struct TesterD
{
    using type = TesterD;
    static constexpr auto value {Variable + 1};

    template<auto, auto Target, auto...>
    struct ProtoPage
    {
        using type = std::index_sequence<TesterD::value, Target>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    double***
#define SUPPOSED_VALUE  \
    2

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Page<static_cast<double>(1)>
    ::type
);

EQUAL_VALUE
(
    Trip<TesterA>
    ::Road<TesterC>
    ::Rail<TesterD>
    ::Page<std::integral_constant<int, 0>{}>
    ::value
);

#undef SUPPOSED_VALUE
#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<double***, float>

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Road<TesterB>
    ::Flow<Emissary>
    ::Page<static_cast<double>(1)>
    ::Mold<int, float, double>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::index_sequence<2, 11>

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterC>
    ::Rail<TesterD>
    ::Sail<Diplomat>
    ::Page<std::integral_constant<int, 0>{}>
    ::Page<10, 11, 12>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif