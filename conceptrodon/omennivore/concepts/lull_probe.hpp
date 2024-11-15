// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_LULL_PROBE_H
#define CONCEPTRODON_OMENNIVORE_LULL_PROBE_H

#include "conceptrodon/lungfish.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept LullProbe = requires 
{typename Lungfish<Structure::template Lull>;};

}}

#endif