// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_COTANIVORE_PASTE_H
#define CONCEPTRODON_COTANIVORE_PASTE_H

#include "conceptrodon/microbiota/cotanis/paste.hpp"

namespace Conceptrodon {
namespace Cotanivore {

using Cotanis::Paste;

template<typename...Packs>
using Paste_t = Paste<Packs...>::type;

}}

#endif