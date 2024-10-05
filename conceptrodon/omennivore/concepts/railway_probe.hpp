// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_RAILWAY_PROBE_H
#define CONCEPTRODON_OMENNIVORE_RAILWAY_PROBE_H

#include "conceptrodon/omennivore/is_railway.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept RailwayProbe = IsRailway_v<Arg>;

}}

#endif