// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_PERFORMANCE_TESTS_TEST_BIND_2ND_H
#define CONCEPTRODON_MOULDVORE_PERFORMANCE_TESTS_TEST_BIND_2ND_H

#include <concepts>
#include "conceptrodon/metafunctions/mouldivore/bind.hpp"
#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/peg.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Mouldivore {
namespace PerformanceTests {
namespace TestBind2nd {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult
    
#define DOUBLE_SHEEP_PREFIX \
    std::integral_constant<int,
#define DOUBLE_SHEEP_MIDDLE \
    *2 >, boost::mp11::mp_arg<
#define DOUBLE_SHEEP_SUFFIX \
    >
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(boost::mp11::mp_bind<Capsule, DOUBLE_SHEEP_SPROUT(120)>::fn<SHEEP_SPROUT(120, *2+1)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#else





/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define DOUBLE_SHEEP_PREFIX \
    std::integral_constant<int,
#define DOUBLE_SHEEP_MIDDLE \
    *2 >, Peg<
#define DOUBLE_SHEEP_SUFFIX \
    +1>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Bind<Capsule>::Mold<DOUBLE_SHEEP_SPROUT(120)>::Mold<SHEEP_SPROUT(120, *2+1)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/

#endif


}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif