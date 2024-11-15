// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GLOW_PROBE_H
#define CONCEPTRODON_OMENNIVORE_GLOW_PROBE_H

#include "conceptrodon/glowworm.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept GlowProbe = requires 
{typename Glowworm<Structure::template Glow>;};

}}

#endif