// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ZERO_PEG_H
#define CONCEPTRODON_OMENNIVORE_ZERO_PEG_H

#include "conceptrodon/descend/descend/omennivore/concepts/pegful.hpp"
#include "conceptrodon/descend/descend/omennivore/concepts/zero_value.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept ZeroPeg
=   Pegful<Arg>
&&  ZeroValue<Arg>;

template<typename...Structures>
concept AllZeroPeg = (...&&ZeroPeg<Structures>);

template<typename...Structures>
concept AnyZeroPeg = (...||ZeroPeg<Structures>);

}}

#endif