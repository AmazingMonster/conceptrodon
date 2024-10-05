// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALMANAC_PROBE_H
#define CONCEPTRODON_OMENNIVORE_ALMANAC_PROBE_H

#include "conceptrodon/omennivore/is_almanac.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept AlmanacProbe = IsAlmanac_v<Arg>;

}}

#endif