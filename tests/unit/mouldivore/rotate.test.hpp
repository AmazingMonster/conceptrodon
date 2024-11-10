// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_ROTATE_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_ROTATE_H

#include "conceptrodon/descend/mouldivore/rotate.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestRotate {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultA = Capsule<SHEEP_SPROUT(200, +40), SHEEP_SPROUT(40)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultA

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Rotate<Capsule>::Page<40>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/



/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultB = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultB

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Rotate<Capsule>::Page<0>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultB

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Rotate<Capsule>::Page<240>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/



/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements)==240)
struct TesterC {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResultC = TesterC<SHEEP_SPROUT(40, +200), SHEEP_SPROUT(200)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResultC

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Rotate<TesterC>::Page<200>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#endif