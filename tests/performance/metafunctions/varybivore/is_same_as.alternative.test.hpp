// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_AS_6TH_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_AS_6TH_H

#include <concepts>
#include "conceptrodon/metafunctions/varybivore/is_same_as.hpp"
#include "conceptrodon/metafunctions/varybivore/is_same.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsSameAs6th {

#ifdef CONCEPTRODON_TEST_ALTERNATIVE_SWITCH

/******************************************************************************************************/
template<auto Target>
struct FlattenedAnyAreSameAs
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        {(...||IsSame<Target, Variables>::value)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    {(...||IsSame<Target, Variables>::value)}; 
};
/******************************************************************************************************/

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
INVALID(FlattenedAnyAreSameAs<-1>::Page<SHEEP_SPROUT(240)>::value);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/

#else

/******************************************************************************************************/
template<auto Target>
struct StructuredAnyAreSameAs
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        {(...||IsSameAs<Target>::template ProtoPage<Variables>::value)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    {(...||IsSameAs<Target>::template ProtoPage<Variables>::value)}; 
};
/******************************************************************************************************/

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
INVALID(StructuredAnyAreSameAs<-1>::Page<SHEEP_SPROUT(240)>::value);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/

#endif


}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif