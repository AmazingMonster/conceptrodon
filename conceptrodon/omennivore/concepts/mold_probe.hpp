// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_MOLD_PROBE_H
#define CONCEPTRODON_OMENNIVORE_MOLD_PROBE_H

#include "conceptrodon/reverie.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept MoldProbe = requires 
{typename Reverie<Structure::template Mold>;};

}}

#endif