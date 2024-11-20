// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEG_ZERO_H
#define CONCEPTRODON_OMENNIVORE_PEG_ZERO_H

#include "conceptrodon/descend/omennivore/concepts/pegful.hpp"
#include "conceptrodon/varybivore/concepts/descend/zero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept PegZero
=   Pegful<Arg>
&&  Varybivore::Zero<Arg::value>;

}}

#endif