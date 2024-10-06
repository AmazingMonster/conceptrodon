// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CONFORMED_H
#define CONCEPTRODON_OMENNIVORE_CONFORMED_H

#include "conceptrodon/omennivore/concepts/almanac_probe.hpp"
#include "conceptrodon/omennivore/concepts/freeway_probe.hpp"
#include "conceptrodon/omennivore/concepts/railway_probe.hpp"
#include "conceptrodon/omennivore/concepts/pottery_probe.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Conformed
=   PotteryProbe<Arg>
||  AlmanacProbe<Arg>
||  FreewayProbe<Arg>
||  RailwayProbe<Arg>;

}}

#endif