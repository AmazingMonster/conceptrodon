// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TEST_OBSERVE_H
#define CONCEPTRODON_PAGELIVORE_TEST_OBSERVE_H

#include "conceptrodon/descend/pagelivore/observe.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/binary_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_binary_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace TestObserve {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedShuttle = Ark<SHEEP_SPROUT(120, *2+1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedShuttle

#include "macaron/fragmental/amenity/instances/define_boolean_sheep.hpp"
SAME_TYPE(Observe<Ark>::Page<BINARY_SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_boolean_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_binary_sheep.hpp"

#endif