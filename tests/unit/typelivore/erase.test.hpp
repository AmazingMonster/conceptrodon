// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ERASE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ERASE_H

#include "conceptrodon/descend/typelivore/erase.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestErase {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultA = Capsule<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResultA

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::Road<Capsule>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
// SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<400, 100>::Road<Capsule>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultB = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResultB

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 40>::Road<Capsule>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements)==180)
struct TesterC {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultC = TesterC<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResultC

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::Road<TesterC>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/



/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<size_t I>
using EraseIndex = Erase<SHEEP_SPROUT(240)>::Page<I>::template Road<std::tuple>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultD = std::tuple<SHEEP_SPROUT(239, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultD
    
SAME_TYPE(EraseIndex<0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultE = std::tuple<SHEEP_SPROUT(40), SHEEP_SPROUT(199, +41)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultE
    
SAME_TYPE(EraseIndex<40>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultF = std::tuple<SHEEP_SPROUT(239)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultF
    
SAME_TYPE(EraseIndex<239>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/


}}}}

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#endif