// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_ERASE_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_ERASE_H

#include <utility>

#include "conceptrodon/descend/pagelivore/cognate_erase.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateErase {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 180)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(CognateErase<Operation>::Page<40, 100>::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
// SAME_TYPE(CognateErase<Operation>::Page<400, 100>::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_1 = Operation<SHEEP_SPROUT(180)>;
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/



/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(CognateErase<Operation>::Page<40, 40>::Page<SHEEP_SPROUT(180)>);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_2 = Operation<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_2

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(CognateErase<Operation>::Page<40, 100>::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<size_t I>
using DismissIndex = CognateErase<Operation>::Page<I>::template Page<SHEEP_SPROUT(181)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_3 = Operation<SHEEP_SPROUT(180, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_3
    
SAME_TYPE(DismissIndex<0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_4 = Operation<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +41)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_4
    
SAME_TYPE(DismissIndex<40>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_5 = Operation<SHEEP_SPROUT(180)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_5
    
SAME_TYPE(DismissIndex<180>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#endif