// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_FALSE_PROBE_H
#define CONCEPTRODON_VARYBIVORE_FALSE_PROBE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Variable>
concept FalseProbe = not static_cast<bool>(Variable);

}}

#endif