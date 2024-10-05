// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_BIND_H
#define CONCEPTRODON_MOULDIVORE_TEST_BIND_H

#include <concepts>
#include "conceptrodon/descend/descend/mouldivore/bind.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/peg.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"
#include "macaron/fragmental/sheep_reversed.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"
#include "macaron/fragmental/amenity/define_sheep_reversed.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestBind {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define DOUBLE_SHEEP_PREFIX \
    std::integral_constant<int,
#define DOUBLE_SHEEP_MIDDLE \
    *2 >, Peg<120 -
#define DOUBLE_SHEEP_SUFFIX \
    >
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep_reversed.hpp"
SAME_TYPE(Bind<Capsule>::Mold<DOUBLE_SHEEP_SPROUT(120)>::Mold<SHEEP_REVERSED_SPROUT(120, *2+1)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep_reversed.hpp"

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"
#include "macaron/fragmental/amenity/undef_sheep_reversed.hpp"

#endif