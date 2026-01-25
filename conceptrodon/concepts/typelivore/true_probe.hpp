// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TRUE_PROBE_H
#define CONCEPTRODON_TYPELIVORE_TRUE_PROBE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Element>
concept TrueProbe = static_cast<bool>(Element::value);

}}

#endif