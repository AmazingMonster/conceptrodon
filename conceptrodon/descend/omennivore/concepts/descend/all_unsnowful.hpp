// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_UNSNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_UNSNOWFUL_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_sailful.hpp"
#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_willful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_dawnful.hpp"
#include "conceptrodon/mouldivore/concepts/all_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AllUnsnowful
=   Mouldivore::AllDeceive<IsSnowful, Args...>
||  AllMoldful<Args...>
||  AllPageful<Args...>
||  AllRoadful<Args...>
||  AllRailful<Args...>
||  AllFlowful<Args...>
||  AllSailful<Args...>
||  AllHailful<Args...>
||  AllCoolful<Args...>
||  AllCalmful<Args...>
||  AllGritful<Args...>
||  AllWillful<Args...>
||  AllGlowful<Args...>
||  AllDawnful<Args...>
;

}}

#endif