// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ERASE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ERASE_H

#include <utility>

#include "conceptrodon/descend/typelivore/erase.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestErase {




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements)==180)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::Road<Operation>);
// SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<100, 40>::Road<Operation>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_1 = Operation<SHEEP_SPROUT(180)>;
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(180)>::Page<40, 40>::Road<Operation>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<size_t I>
using EraseIndex = Erase<SHEEP_SPROUT(181)>::Page<I>::template Road<Operation>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_3 = Operation<SHEEP_SPROUT(180, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_3
    
SAME_TYPE(EraseIndex<0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_4 = Operation<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +41)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_4
    
SAME_TYPE(EraseIndex<40>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_5 = Operation<SHEEP_SPROUT(180)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_5
    
SAME_TYPE(EraseIndex<180>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#endif