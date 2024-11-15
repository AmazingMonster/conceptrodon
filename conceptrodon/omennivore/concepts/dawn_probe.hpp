// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_DAWN_PROBE_H
#define CONCEPTRODON_OMENNIVORE_DAWN_PROBE_H

#include "conceptrodon/daydream.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept DawnProbe = requires 
{typename Daydream<Structure::template Dawn>;};

}}

#endif