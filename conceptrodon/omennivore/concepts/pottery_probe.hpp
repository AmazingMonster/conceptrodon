// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_POTTERY_PROBE_H
#define CONCEPTRODON_OMENNIVORE_POTTERY_PROBE_H

#include "conceptrodon/omennivore/is_pottery.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept PotteryProbe = IsPottery_v<Arg>;

}}

#endif