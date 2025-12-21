// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEG_ZERO_H
#define CONCEPTRODON_OMENNIVORE_PEG_ZERO_H

#include "conceptrodon/metafunctions/omennivore/concepts/pegful.hpp"
#include "conceptrodon/metafunctions/varybivore/concepts/zero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept PegZero
=   Pegful<Arg>
&&  Varybivore::Zero<Arg::value>;

}}

#endif