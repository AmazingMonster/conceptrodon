// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_REVERSE_2ND_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_REVERSE_2ND_H

#include "concepts"
#include "conceptrodon/mouldivore/cognate_reverse.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/sheep_reversed.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_sheep_reversed.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateReverse2nd {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using OrderedCapsule = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep_reversed.hpp"
using SuppesedCapsule = Capsule<SHEEP_REVERSED_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep_reversed.hpp"
/******************************************************************************************************/




#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SuppesedCapsule

SAME_TYPE(boost::mp11::mp_reverse<OrderedCapsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#else





/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SuppesedCapsule

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateReverse<Capsule>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#endif




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_sheep_reversed.hpp"

#endif