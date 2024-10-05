// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_IS_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_TEST_IS_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/varybivore/is_bounded_by_left_closed_right_open_interval.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsBoundedByLeftClosedRightOpenInterval {

VALID(IsBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<0>);
VALID(IsBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<0.5>);
INVALID(IsBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<1>);
INVALID(IsBoundedByLeftClosedRightOpenInterval<0, 1>::Page_v<2>);

}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif