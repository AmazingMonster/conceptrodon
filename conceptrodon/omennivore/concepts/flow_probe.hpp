// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FLOW_PROBE_H
#define CONCEPTRODON_OMENNIVORE_FLOW_PROBE_H

#include "conceptrodon/florican.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept FlowProbe = requires 
{typename Florican<Structure::template Flow>;};

}}

#endif