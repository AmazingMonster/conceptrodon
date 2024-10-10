// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FLOW_PROBE_H
#define CONCEPTRODON_OMENNIVORE_FLOW_PROBE_H

#include "conceptrodon/lullaby.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept FlowProbe = requires 
{typename Lullaby<Structure::template Flow>;};

}}

#endif