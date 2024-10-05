// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PAGE_PROBE_H
#define CONCEPTRODON_OMENNIVORE_PAGE_PROBE_H

#include "conceptrodon/phantom.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept PageProbe = requires 
{typename Phantom<Structure::template Page>;};

}}

#endif