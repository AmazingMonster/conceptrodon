// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HAIL_PROBE_H
#define CONCEPTRODON_OMENNIVORE_HAIL_PROBE_H

#include "conceptrodon/halfmoon.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept HailProbe = requires 
{typename Halfmoon<Structure::template Hail>;};

}}

#endif