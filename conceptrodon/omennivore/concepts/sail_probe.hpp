// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SAIL_PROBE_H
#define CONCEPTRODON_OMENNIVORE_SAIL_PROBE_H

#include "conceptrodon/sailfish.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept SailProbe = requires 
{typename Sailfish<Structure::template Sail>;};

}}

#endif