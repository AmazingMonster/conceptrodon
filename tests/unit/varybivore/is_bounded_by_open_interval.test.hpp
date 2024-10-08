// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_BOUNDED_BY_OPEN_INTERVAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/varybivore/is_bounded_by_open_interval.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsBoundedByOpenInterval {

INVALID(IsBoundedByOpenInterval<0, 1>::Page_v<0>);
VALID(IsBoundedByOpenInterval<0, 1>::Page_v<0.5>);
INVALID(IsBoundedByOpenInterval<0, 1>::Page_v<1>);
INVALID(IsBoundedByOpenInterval<0, 1>::Page_v<2>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif