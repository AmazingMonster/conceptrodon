// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_SNOWFUL_H

#include "conceptrodon/metafunctions/omennivore/is_snowful.hpp"
#include "conceptrodon/concepts/mouldivore/passed.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Snowful = Mouldivore::Passed<IsSnowful, Arg>;

}}

#endif