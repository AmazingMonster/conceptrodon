// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SAIL_PROBE_H
#define CONCEPTRODON_OMENNIVORE_SAIL_PROBE_H

#include "conceptrodon/revelation.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept SailProbe = requires 
{typename Revelation<Structure::template Sail>;};

}}

#endif