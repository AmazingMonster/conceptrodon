// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_TRIP_H
#define CONCEPTRODON_MOULDIVORE_TEST_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/mouldivore/trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "conceptrodon/emissary.hpp"
#include "conceptrodon/diplomat.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestTrip {




/******************************************************************************************************/
template<typename Element>
struct TesterA
{ 
    using type = Element*;

    template<typename, typename Target, typename...>
    struct ProtoMold
    {
        using type = std::tuple<TesterA::type, Target>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<typename Element>
requires Omennivore::Valuable<Element>
struct TesterA<Element>
{ 
    using type = Element;
    static constexpr auto value {Element::value};

    template<typename, typename Target, typename...>
    struct ProtoMold
    {
        using type = std::tuple<TesterA::type, Target>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<auto, auto Target, auto...>
    struct ProtoPage
    {
        using type = std::index_sequence<TesterA::value, Target>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

template<typename Element>
requires Omennivore::Valuable<Element>
struct TesterB
{
    using type = TesterB;
    static constexpr auto value {Element::value + 1};
};

template<auto Variable>
struct TesterC
{
    using type = TesterC;
    static constexpr auto value {Variable + 1};
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    int***
#define SUPPOSED_VALUE  \
    2

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterA>
    ::Road<TesterA>
    ::Mold<int>
    ::type
);

EQUAL_VALUE
(
    Trip<TesterA>
    ::Road<TesterA>
    ::Road<TesterB>
    ::Rail<TesterC>
    ::Mold<std::integral_constant<int, 0>>
    ::value
);

#undef SUPPOSED_VALUE
#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::tuple<int**, float>

SAME_TYPE
(
    Trip<TesterA>
    ::Road<TesterA>
    ::Flow<Emissary>
    ::Mold<int>
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
    ::Road<TesterB>
    ::Rail<TesterC>
    ::Road<TesterA>
    ::Sail<Diplomat>
    ::Mold<std::integral_constant<int, 0>>
    ::Page<10, 11, 12>
    ::type
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif