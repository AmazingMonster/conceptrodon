// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GLOWLY_H
#define CONCEPTRODON_OMENNIVORE_GLOWLY_H

#include "conceptrodon/gly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Glowly = requires 
{typename Gly<Structure::template Glow>;};

}}

#endif