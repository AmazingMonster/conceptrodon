// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TEST_HAS_H
#define CONCEPTRODON_TYPELIVORE_TEST_HAS_H

#include <concepts>
#include "conceptrodon/descend/typelivore/has.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace TestHas {
    
    



#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(boost::mp11::mp_has<Capsule<SHEEP_SPROUT(240)>, std::integral_constant<int, 10>>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(boost::mp11::mp_has<Capsule<SHEEP_SPROUT(240), std::integral_constant<int, 39>>, std::integral_constant<int, 39>>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(boost::mp11::mp_has<Capsule<SHEEP_SPROUT(240), std::integral_constant<int, 39>>, std::integral_constant<int, -1>>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




#else




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(Has<SHEEP_SPROUT(240)>::Mold<std::integral_constant<int, 10>>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(Has<SHEEP_SPROUT(240), std::integral_constant<int, 39>>::Mold<std::integral_constant<int, 39>>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
INVALID(Has<SHEEP_SPROUT(240), std::integral_constant<int, 39>>::Mold<std::integral_constant<int, -1>>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




#endif




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif