// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GLOWLESS_H
#define CONCEPTRODON_OMENNIVORE_GLOWLESS_H

#include "conceptrodon/gly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Glowless = not requires 
{typename Gly<Structure::template Glow>;};

}}

#endif