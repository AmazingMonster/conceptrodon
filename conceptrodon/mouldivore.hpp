// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#include "conceptrodon/mouldivore/agent.hpp"
#include "conceptrodon/mouldivore/among.hpp"
#include "conceptrodon/mouldivore/bind_back.hpp"
#include "conceptrodon/mouldivore/bind_front.hpp"
#include "conceptrodon/mouldivore/conceal.hpp"
#include "conceptrodon/mouldivore/conjunction.hpp"
#include "conceptrodon/mouldivore/disjunction.hpp"
#include "conceptrodon/mouldivore/find.hpp"
#include "conceptrodon/mouldivore/fold_left.hpp"
#include "conceptrodon/mouldivore/fold_left_first.hpp"
#include "conceptrodon/mouldivore/fold_right.hpp"
#include "conceptrodon/mouldivore/fold_right_last.hpp"
#include "conceptrodon/mouldivore/independent_find.hpp"
#include "conceptrodon/mouldivore/independent_left_interview.hpp"
#include "conceptrodon/mouldivore/independent_right_interview.hpp"
#include "conceptrodon/mouldivore/is_specialization.hpp"
#include "conceptrodon/mouldivore/left_interview.hpp"
#include "conceptrodon/mouldivore/look_for.hpp"
#include "conceptrodon/mouldivore/negation.hpp"
#include "conceptrodon/mouldivore/permit_if.hpp"
#include "conceptrodon/mouldivore/repack.hpp"
#include "conceptrodon/mouldivore/reveal.hpp"
#include "conceptrodon/mouldivore/right_interview.hpp"
#include "conceptrodon/mouldivore/situational.hpp"
#include "conceptrodon/mouldivore/swap.hpp"
#include "conceptrodon/mouldivore/trek.hpp"
#include "conceptrodon/mouldivore/trip.hpp"

#include "conceptrodon/descend/mouldivore/allow_if.hpp"
#include "conceptrodon/descend/mouldivore/dismiss.hpp"
#include "conceptrodon/descend/mouldivore/erase.hpp"
#include "conceptrodon/descend/mouldivore/front.hpp"
#include "conceptrodon/descend/mouldivore/gauge.hpp"
#include "conceptrodon/descend/mouldivore/grade.hpp"
#include "conceptrodon/descend/mouldivore/harvest.hpp"
#include "conceptrodon/descend/mouldivore/inject.hpp"
#include "conceptrodon/descend/mouldivore/left_review.hpp"
#include "conceptrodon/descend/mouldivore/metamorphose.hpp"
#include "conceptrodon/descend/mouldivore/plume.hpp"
#include "conceptrodon/descend/mouldivore/preen.hpp"
#include "conceptrodon/descend/mouldivore/recur.hpp"
#include "conceptrodon/descend/mouldivore/refurbish.hpp"
#include "conceptrodon/descend/mouldivore/renovate.hpp"
#include "conceptrodon/descend/mouldivore/repeat.hpp"
#include "conceptrodon/descend/mouldivore/reverse.hpp"
#include "conceptrodon/descend/mouldivore/right_review.hpp"
#include "conceptrodon/descend/mouldivore/roam.hpp"
#include "conceptrodon/descend/mouldivore/rotate.hpp"
#include "conceptrodon/descend/mouldivore/rove.hpp"
#include "conceptrodon/descend/mouldivore/short_defer.hpp"
#include "conceptrodon/descend/mouldivore/short_delay.hpp"
#include "conceptrodon/descend/mouldivore/short_pause.hpp"
#include "conceptrodon/descend/mouldivore/short_remit.hpp"
#include "conceptrodon/descend/mouldivore/sieve.hpp"
#include "conceptrodon/descend/mouldivore/slice.hpp"
#include "conceptrodon/descend/mouldivore/transform.hpp"
#include "conceptrodon/descend/mouldivore/trim.hpp"

#include "conceptrodon/descend/descend/mouldivore/alter.hpp"
#include "conceptrodon/descend/descend/mouldivore/bind.hpp"
#include "conceptrodon/descend/descend/mouldivore/filter.hpp"
#include "conceptrodon/descend/descend/mouldivore/insert.hpp"
#include "conceptrodon/descend/descend/mouldivore/modify.hpp"
#include "conceptrodon/descend/descend/mouldivore/remove.hpp"