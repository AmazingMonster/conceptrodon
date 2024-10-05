// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_REPACK_H
#define CONCEPTRODON_OMENNIVORE_REPACK_H

#include "conceptrodon/omennivore/concepts/pottery_probe.hpp"
#include "conceptrodon/omennivore/concepts/freeway_probe.hpp"
#include "conceptrodon/omennivore/concepts/railway_probe.hpp"
#include "conceptrodon/cotanivore/repack.hpp"
#include "conceptrodon/sequnivore/repack.hpp"
#include "conceptrodon/warehivore/repack.hpp"
#include "conceptrodon/stockivore/repack.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct Repack
: public Sequnivore::Repack<Packages...>
{};

template<typename...Packages>
requires (... && PotteryProbe<Packages>)
struct Repack<Packages...>
: public Cotanivore::Repack<Packages...>
{};
template<typename...Packages>
requires (... && FreewayProbe<Packages>)
struct Repack<Packages...>
: public Warehivore::Repack<Packages...>
{};

template<typename...Packages>
requires (... && RailwayProbe<Packages>)
struct Repack<Packages...>
: public Stockivore::Repack<Packages...>
{};

}}

#endif