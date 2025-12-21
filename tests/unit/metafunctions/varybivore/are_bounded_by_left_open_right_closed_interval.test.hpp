// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ARE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_ARE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H

#include "conceptrodon/metafunctions/varybivore/are_bounded_by_left_closed_right_open_interval.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAreBoundedByLeftClosedRightOpenInterval {




/******************************************************************************************************/
VALID(AreBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<0, 0.5, 0.8>);
INVALID(AreBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<0, 1>);
INVALID(AreBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<0, -1>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif