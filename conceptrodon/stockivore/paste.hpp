// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_STOCKIVORE_PASTE_H
#define CONCEPTRODON_STOCKIVORE_PASTE_H

#include "conceptrodon/microbiota/stockii/typical_paste.hpp"

namespace Conceptrodon {
namespace Stockivore {

template<typename...Packs>
using Paste = Stockii::TypicalPaste<Packs...>::type;

}}

#endif