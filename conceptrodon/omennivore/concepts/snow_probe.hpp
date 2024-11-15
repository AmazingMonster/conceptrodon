// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SNOW_PROBE_H
#define CONCEPTRODON_OMENNIVORE_SNOW_PROBE_H

#include "conceptrodon/snowfall.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept SnowProbe = requires 
{typename Snowfall<Structure::template Snow>;};

}}

#endif