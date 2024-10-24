// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_RAIL_PROBE_H
#define CONCEPTRODON_OMENNIVORE_RAIL_PROBE_H

#include "conceptrodon/travail.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept RailProbe = requires
{typename Travail<Structure::template Rail>;};

}}

#endif