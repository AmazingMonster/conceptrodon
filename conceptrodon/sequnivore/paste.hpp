// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SEQUNIVORE_PASTE_H
#define CONCEPTRODON_SEQUNIVORE_PASTE_H

#include "conceptrodon/microbiota/sequena/paste.hpp"

namespace Conceptrodon {
namespace Sequnivore {

using Sequena::Paste;

template<typename...Packs>
using Paste_t = Paste<Packs...>::type;

}}

#endif