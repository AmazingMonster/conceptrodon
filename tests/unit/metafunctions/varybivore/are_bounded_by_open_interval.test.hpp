// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_ARE_BOUNDED_BY_OPEN_INTERVAL_H

#include <type_traits>
#include "conceptrodon/varybivore/are_bounded_by_open_interval.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsBoundedByOpenInterval {

INVALID(AreBoundedByOpenInterval<0, 1>::Page_v<0, 0.3>);
VALID(AreBoundedByOpenInterval<0, 1>::Page_v<0.5, 0.3>);
INVALID(AreBoundedByOpenInterval<0, 1>::Page_v<1, 2>);
INVALID(AreBoundedByOpenInterval<0, 1>::Page_v<2, -1>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif