// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FREEWAY_PROBE_H
#define CONCEPTRODON_OMENNIVORE_FREEWAY_PROBE_H

#include "conceptrodon/omennivore/is_freeway.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept FreewayProbe = IsFreeway_v<Arg>;

}}

#endif