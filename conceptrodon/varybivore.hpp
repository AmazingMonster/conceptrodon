// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#include "conceptrodon/varybivore/concepts/descend/descend/bounded_by_closed_interval.hpp"
#include "conceptrodon/varybivore/concepts/descend/descend/bounded_by_left_closed_right_open_interval.hpp"
#include "conceptrodon/varybivore/concepts/descend/descend/bounded_by_left_open_right_closed_interval.hpp"
#include "conceptrodon/varybivore/concepts/descend/bounded_by_open_interval.hpp"
#include "conceptrodon/varybivore/concepts/descend/greater.hpp"
#include "conceptrodon/varybivore/concepts/descend/no_greater.hpp"
#include "conceptrodon/varybivore/concepts/descend/no_less.hpp"
#include "conceptrodon/varybivore/concepts/descend/unequal.hpp"
#include "conceptrodon/varybivore/concepts/clarify.hpp"
#include "conceptrodon/varybivore/concepts/different.hpp"
#include "conceptrodon/varybivore/concepts/equal.hpp"
#include "conceptrodon/varybivore/concepts/falsify.hpp"
#include "conceptrodon/varybivore/concepts/less.hpp"
#include "conceptrodon/varybivore/concepts/same.hpp"
#include "conceptrodon/varybivore/add.hpp"
#include "conceptrodon/varybivore/among.hpp"
#include "conceptrodon/varybivore/boolean.hpp"
#include "conceptrodon/varybivore/conditional.hpp"
#include "conceptrodon/varybivore/find.hpp"
#include "conceptrodon/varybivore/fold_left_first.hpp"
#include "conceptrodon/varybivore/fold_left.hpp"
#include "conceptrodon/varybivore/fold_right.hpp"
#include "conceptrodon/varybivore/is_bounded_by_closed_interval.hpp"
#include "conceptrodon/varybivore/is_bounded_by_left_closed_right_open_interval.hpp"
#include "conceptrodon/varybivore/is_bounded_by_left_open_right_closed_interval.hpp"
#include "conceptrodon/varybivore/is_bounded_by_open_interval.hpp"
#include "conceptrodon/varybivore/is_different.hpp"
#include "conceptrodon/varybivore/is_equal.hpp"
#include "conceptrodon/varybivore/is_greater.hpp"
#include "conceptrodon/varybivore/is_less.hpp"
#include "conceptrodon/varybivore/is_no_greater.hpp"
#include "conceptrodon/varybivore/is_no_less.hpp"
#include "conceptrodon/varybivore/is_same.hpp"
#include "conceptrodon/varybivore/is_unequal.hpp"
#include "conceptrodon/varybivore/left_interview.hpp"
#include "conceptrodon/varybivore/look_for.hpp"
#include "conceptrodon/varybivore/maximum.hpp"
#include "conceptrodon/varybivore/minimum.hpp"
#include "conceptrodon/varybivore/minus.hpp"
#include "conceptrodon/varybivore/plus.hpp"
#include "conceptrodon/varybivore/right_interview.hpp"
#include "conceptrodon/varybivore/sensible_left_interview.hpp"
#include "conceptrodon/varybivore/sensible_left_interview.hpp"
#include "conceptrodon/varybivore/subtract.hpp"


#include "conceptrodon/descend/varybivore/amidst.hpp"
#include "conceptrodon/descend/varybivore/are_distinct.hpp"
#include "conceptrodon/descend/varybivore/are_overlapping.hpp"
#include "conceptrodon/descend/varybivore/contains.hpp"
#include "conceptrodon/descend/varybivore/dismiss.hpp"
#include "conceptrodon/descend/varybivore/diversity.hpp"
#include "conceptrodon/descend/varybivore/erase.hpp"
#include "conceptrodon/descend/varybivore/flip.hpp"
#include "conceptrodon/descend/varybivore/front.hpp"
#include "conceptrodon/descend/varybivore/gauge.hpp"
#include "conceptrodon/descend/varybivore/grade.hpp"
#include "conceptrodon/descend/varybivore/inject.hpp"
#include "conceptrodon/descend/varybivore/observe.hpp"
#include "conceptrodon/descend/varybivore/plume.hpp"
#include "conceptrodon/descend/varybivore/pop.hpp"
#include "conceptrodon/descend/varybivore/preen.hpp"
#include "conceptrodon/descend/varybivore/refurbish.hpp"
#include "conceptrodon/descend/varybivore/reiterate.hpp"
#include "conceptrodon/descend/varybivore/renovate.hpp"
#include "conceptrodon/descend/varybivore/rise.hpp"
#include "conceptrodon/descend/varybivore/rotate.hpp"
#include "conceptrodon/descend/varybivore/set_contains.hpp"
#include "conceptrodon/descend/varybivore/slice.hpp"
#include "conceptrodon/descend/varybivore/trim.hpp"


#include "conceptrodon/descend/descend/varybivore/amid.hpp"
#include "conceptrodon/descend/descend/varybivore/are_unique.hpp"
#include "conceptrodon/descend/descend/varybivore/duplicate.hpp"
#include "conceptrodon/descend/descend/varybivore/make_set.hpp"
#include "conceptrodon/descend/descend/varybivore/upend.hpp"