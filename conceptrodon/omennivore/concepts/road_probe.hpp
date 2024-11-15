// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ROAD_PROBE_H
#define CONCEPTRODON_OMENNIVORE_ROAD_PROBE_H

#include "conceptrodon/legation.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept RoadProbe = requires 
{typename Legation<Structure::template Road>;};

}}

#endif