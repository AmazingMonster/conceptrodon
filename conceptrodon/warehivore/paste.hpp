// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_WAREHIVORE_PASTE_H
#define CONCEPTRODON_WAREHIVORE_PASTE_H

#include "conceptrodon/microbiota/waretus/paste.hpp"

namespace Conceptrodon {
namespace Warehivore {

using Waretus::Paste;

template<typename...Packs>
using Paste_t = Paste<Packs...>::type;

}}

#endif