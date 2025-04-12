// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NONOVERLOADED_FUNCTION_OBJECT_PROBE_H
#define CONCEPTRODON_FUNCTIVORE_NONOVERLOADED_FUNCTION_OBJECT_PROBE_H

namespace Conceptrodon {
namespace Functivore {

template<typename FO>
concept NonOverloadedFunctionObjectProbe
= requires {&FO::operator();};

}}

#endif