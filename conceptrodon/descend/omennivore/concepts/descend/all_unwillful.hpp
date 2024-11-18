// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_UNWILLFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_UNWILLFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_gritful.hpp"
#include "conceptrodon/omennivore/is_willful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_dawnful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAllUnwillful
= (...&&(not IsWillful<Args>::value));

template<typename...Args>
concept AllUnwillful
=   JustAllUnwillful<Args...>
||  AllMoldful<Args...>
||  AllPageful<Args...>
||  AllRoadful<Args...>
||  AllRailful<Args...>
||  AllFlowful<Args...>
||  AllSailful<Args...>
||  AllSnowful<Args...>
||  AllHailful<Args...>
||  AllCoolful<Args...>
||  AllCalmful<Args...>
||  AllGritful<Args...>
||  AllGlowful<Args...>
||  AllDawnful<Args...>
;

}}

#endif