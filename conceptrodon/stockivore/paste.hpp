// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_STOCKIVORE_PASTE_H
#define CONCEPTRODON_STOCKIVORE_PASTE_H

#include "conceptrodon/microbiota/stockii/paste.hpp"

namespace Conceptrodon {
namespace Stockivore {

using Stockii::Paste;

template<typename...Packs>
using Paste_t = Paste<Packs...>::type;

}}

#endif