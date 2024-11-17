// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_COOL_PROBE_H
#define CONCEPTRODON_OMENNIVORE_COOL_PROBE_H

#include "conceptrodon/coalfish.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept CoolProbe = requires 
{typename Coalfish<Structure::template Cool>;};

}}

#endif