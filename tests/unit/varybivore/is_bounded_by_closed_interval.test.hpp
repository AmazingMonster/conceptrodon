// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_BOUNDED_BY_CLOSED_INTERVAL_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_BOUNDED_BY_CLOSED_INTERVAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/varybivore/is_bounded_by_closed_interval.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestIsBoundedByClosedInterval {

VALID(IsBoundedByClosedInterval<0, 1>::Page_v<0>);
VALID(IsBoundedByClosedInterval<0, 1>::Page_v<0.5>);
VALID(IsBoundedByClosedInterval<0, 1>::Page_v<1>);
INVALID(IsBoundedByClosedInterval<0, 1>::Page_v<2>);

}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif