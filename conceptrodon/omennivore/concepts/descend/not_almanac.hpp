// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_NOT_ALMANAC_H
#define CONCEPTRODON_OMENNIVORE_NOT_ALMANAC_H

#include "conceptrodon/omennivore/concepts/almanac_probe.hpp"
#include "conceptrodon/omennivore/concepts/freeway_probe.hpp"
#include "conceptrodon/omennivore/concepts/railway_probe.hpp"
#include "conceptrodon/omennivore/concepts/pottery_probe.hpp"

namespace Conceptrodon {

namespace Ominuci {
    
template<typename Arg>
concept IndeedNotAlmanac 
= not Omennivore::AlmanacProbe<Arg>;

}

namespace Omennivore {

template<typename Arg>
concept NotAlmanac 
=   Ominuci::IndeedNotAlmanac<Arg>
||  FreewayProbe<Arg>
||  RailwayProbe<Arg>
||  PotteryProbe<Arg>;

}}

#endif