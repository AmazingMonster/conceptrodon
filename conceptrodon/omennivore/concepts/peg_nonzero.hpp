// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEG_NONZERO_H
#define CONCEPTRODON_OMENNIVORE_PEG_NONZERO_H

#include "conceptrodon/omennivore/concepts/pegful.hpp"
#include "conceptrodon/varybivore/concepts/nonzero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept PegNonzero
=   Pegful<Arg>
&&  Varybivore::Nonzero<Arg::value>;

}}

#endif