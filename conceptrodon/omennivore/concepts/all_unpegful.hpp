// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_UNPEGFUL_H

#include "conceptrodon/mouldivore/concepts/all_deceive.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/utilities/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AllUnpegful
= Mouldivore::AllDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;

}}

#endif