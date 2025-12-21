// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEG_NONZERO_H
#define CONCEPTRODON_OMENNIVORE_PEG_NONZERO_H

#include "conceptrodon/concepts/omennivore/pegful.hpp"
#include "conceptrodon/concepts/varybivore/nonzero.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept PegNonzero
=   Pegful<Arg>
&&  Varybivore::Nonzero<Arg::value>;

}}

#endif