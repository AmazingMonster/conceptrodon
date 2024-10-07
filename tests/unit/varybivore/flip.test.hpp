// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_FLIP_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_FLIP_H

#include "concepts"
#include "conceptrodon/descend/varybivore/flip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/sheep_reversed.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_sheep_reversed.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestFlip {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep_reversed.hpp"
using SuppesedShuttle = Shuttle<SHEEP_REVERSED_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep_reversed.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SuppesedShuttle

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Flip<SHEEP_SPROUT(240)>::type);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_sheep_reversed.hpp"

#endif