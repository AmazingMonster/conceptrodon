// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ARE_OVERLAPPING_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_ARE_OVERLAPPING_H

#include <utility>

#include "conceptrodon/descend/typelivore/are_overlapping.hpp"

#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAreOverlapping {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
static_assert
(
    std::is_same_v
    <
        AreOverlapping<SHEEP_SPROUT(240)>
        ::Mold<SHEEP_SPROUT(120)>
        ::type
        ,
        void
    >
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
static_assert
(
    std::is_same_v
    <
        AreOverlapping<SHEEP_SPROUT(240)>
        ::Mold<std::integral_constant<int, 10>>
        ::type
        ,
        void
    >
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/





/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
static_assert
(
    ! std::is_same_v
    <
        AreOverlapping<SHEEP_SPROUT(40)>
        ::Mold<SHEEP_SPROUT(40, +40)>
        ::type
        ,
        void
    >
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif