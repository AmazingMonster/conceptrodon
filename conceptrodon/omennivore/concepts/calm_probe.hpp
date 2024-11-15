// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CALM_PROBE_H
#define CONCEPTRODON_OMENNIVORE_CALM_PROBE_H

#include "conceptrodon/camellia.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept CalmProbe = requires 
{typename Camellia<Structure::template Calm>;};

}}

#endif