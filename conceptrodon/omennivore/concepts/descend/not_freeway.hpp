// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_NOT_FREEWAY_H
#define CONCEPTRODON_OMENNIVORE_NOT_FREEWAY_H

#include "conceptrodon/omennivore/concepts/almanac_probe.hpp"
#include "conceptrodon/omennivore/concepts/freeway_probe.hpp"
#include "conceptrodon/omennivore/concepts/railway_probe.hpp"
#include "conceptrodon/omennivore/concepts/pottery_probe.hpp"

namespace Conceptrodon {

namespace Ominuci {
    
template<typename Arg>
concept IndeedNotFreeway 
= not Omennivore::FreewayProbe<Arg>;

}

namespace Omennivore {

template<typename Arg>
concept NotFreeway
=   Ominuci::IndeedNotFreeway<Arg>
||  AlmanacProbe<Arg>
||  RailwayProbe<Arg>
||  PotteryProbe<Arg>;

}}

#endif