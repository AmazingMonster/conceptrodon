// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNCONFORMED_H
#define CONCEPTRODON_OMENNIVORE_UNCONFORMED_H

#include "conceptrodon/omennivore/concepts/descend/not_almanac.hpp"
#include "conceptrodon/omennivore/concepts/descend/not_freeway.hpp"
#include "conceptrodon/omennivore/concepts/descend/not_railway.hpp"
#include "conceptrodon/omennivore/concepts/descend/not_pottery.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Unconformed
=   Ominuci::IndeedNotPottery<Arg>
||  Ominuci::IndeedNotAlmanac<Arg>
||  Ominuci::IndeedNotFreeway<Arg>
||  Ominuci::IndeedNotRailway<Arg>;

}}

#endif