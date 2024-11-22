// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_SAME_AS_2ND_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_IS_SAME_AS_2ND_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/typelivore/is_same_as.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestIsSameAs2nd {

#ifdef CONCEPTRODON_TEST_ALTERNATIVE_SWITCH

/******************************************************************************************************/
template<typename Target>
struct FlattenedAnyAreSameAs
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {(...||std::is_same<Target, Elements>::value)}; 
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Elements>
    static constexpr bool Mold_v 
    {(...||std::is_same<Target, Elements>::value)}; 
};
/******************************************************************************************************/

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(FlattenedAnyAreSameAs<std::integral_constant<int, -1>>::Mold<SHEEP_SPROUT(240)>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/

#else

/******************************************************************************************************/
template<typename Target>
struct StructuredAnyAreSameAs
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {(...||IsSameAs<Target>::template ProtoMold<Elements>::value)}; 
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Elements>
    static constexpr bool Mold_v 
    {(...||IsSameAs<Target>::template ProtoMold<Elements>::value)}; 
};
/******************************************************************************************************/

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(StructuredAnyAreSameAs<std::integral_constant<int, -1>>::Mold<SHEEP_SPROUT(240)>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/

#endif


}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif