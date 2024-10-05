// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_NONZERO_PEG_H
#define CONCEPTRODON_OMENNIVORE_NONZERO_PEG_H

#include "conceptrodon/descend/omennivore/concepts/peg_probe.hpp"
#include "conceptrodon/descend/omennivore/concepts/nonzero_value.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept NonzeroPeg = PegProbe<Arg> && NonzeroValue<Arg>;

}}

#endif