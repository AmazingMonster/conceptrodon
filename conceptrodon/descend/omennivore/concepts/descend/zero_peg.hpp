// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ZERO_PEG_H
#define CONCEPTRODON_OMENNIVORE_ZERO_PEG_H

#include "conceptrodon/descend/omennivore/concepts/peg_probe.hpp"
#include "conceptrodon/descend/omennivore/concepts/zero_value.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept ZeroPeg = PegProbe<Arg> && ZeroValue<Arg>;

}}

#endif