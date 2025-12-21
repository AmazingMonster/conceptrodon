// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_PERFORMANCE_TESTS_TEST_COGNATE_FILTER_2ND_H
#define CONCEPTRODON_MOULDVORE_PERFORMANCE_TESTS_TEST_COGNATE_FILTER_2ND_H

#include <type_traits>
#include <concepts>
#include "conceptrodon/metafunctions/mouldivore/cognate_filter.hpp"
#include "conceptrodon/utilities/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace PerformanceTests {
namespace TestCognateFilter2nd {




/******************************************************************************************************/
template<typename Integer>
struct IsEven
{
    static constexpr bool value = Integer::value % 2 == 0;
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(120, * 2 + 1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using CapsuleTester = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(boost::mp11::mp_remove_if<CapsuleTester, IsEven>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#else





/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateFilter<Capsule>::Road<IsEven>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#endif

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

}}}}

#endif