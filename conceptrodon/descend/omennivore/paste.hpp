// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PASTE_H
#define CONCEPTRODON_OMENNIVORE_PASTE_H

#include "conceptrodon/omennivore/concepts/pottery_probe.hpp"
#include "conceptrodon/omennivore/concepts/freeway_probe.hpp"
#include "conceptrodon/omennivore/concepts/railway_probe.hpp"
#include "conceptrodon/cotanivore/paste.hpp"
#include "conceptrodon/sequnivore/paste.hpp"
#include "conceptrodon/warehivore/paste.hpp"
#include "conceptrodon/stockivore/paste.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct Paste
: public Sequnivore::Paste<Packages...>
{};

template<typename...Packages>
requires (... && PotteryProbe<Packages>)
struct Paste<Packages...>
: public Cotanivore::Paste<Packages...>
{};
template<typename...Packages>
requires (... && FreewayProbe<Packages>)
struct Paste<Packages...>
: public Warehivore::Paste<Packages...>
{};

template<typename...Packages>
requires (... && RailwayProbe<Packages>)
struct Paste<Packages...>
: public Stockivore::Paste<Packages...>
{};

template<typename...Packables>
using Paste_t = Paste<Packables...>::type;

}}

#endif