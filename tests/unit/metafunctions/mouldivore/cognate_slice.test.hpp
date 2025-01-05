// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_SLICE_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_SLICE_H

#include "conceptrodon/mouldivore/cognate_slice.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateSlice {




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 200)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(200, +60)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateSlice<Operation>::Page<60, 260>::Mold<SHEEP_SPROUT(300)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 0)
struct Operation_1 {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_1 = Operation_1<>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateSlice<Operation_1>::Page<40, 40>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_2 = Operation<SHEEP_SPROUT(200, +40)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_2

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateSlice<Operation>::Page<40>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_3 = Operation<SHEEP_SPROUT(200)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_3

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateSlice<Operation>::Page<0>::Mold<SHEEP_SPROUT(200)>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateSlice<Operation_1>::Page<200>::Mold<SHEEP_SPROUT(200)>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 1)
struct Operation_2 {};
/******************************************************************************************************/




/******************************************************************************************************/
using SupposedResult_4 = Operation_2<std::integral_constant<int, 199>>;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_4

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateSlice<Operation_2>::Page<199>::Mold<SHEEP_SPROUT(200)>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif