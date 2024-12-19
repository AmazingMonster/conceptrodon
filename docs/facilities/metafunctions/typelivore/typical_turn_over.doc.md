<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalTurnOver`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-6">To Index</a></p>

## Description

`Typelivore::TypicalTurnOver` accepts a list of elements and returns a `Capsule` packed with the previously provided elements but in reversed order.

<pre><code>   Element<sub>0</sub>, Element<sub>1</sub>, ..., Element<sub>n</sub>
-> Element<sub>n</sub>, Element<sub>n-1</sub>, ..., Element<sub>0</sub></code></pre>

## Type Signature

```Haskell
TypicalTurnOver ::   typename...
                  -> typename
```

## Structure

```C++
template<typename...>
struct TypicalTurnOver
{
    using type = RESULT;
};
```

## Examples

We will turn over `int, int*, int**, int**`.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int**, int**, int*, int>;

using Result = TypicalTurnOver<int, int*, int**, int**>
::type;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `TypicalTurnOver` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several elements in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename>
struct ExtendBack {};

template<template<typename...> class Container, typename...Elements>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Endings>
    using Mold = Container<Elements..., Endings...>;
};
```

Here's a simplified version of the implementation:

```C++
template<typename...>
struct Capsule;

template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type 
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BekkpjgJBIeEsUTHxdpgOaUIETMQEGT5%2BXLaY9nkM1bUEBWGR0XG2NXUNWc0KQ93BvcX9sQCUtqhexMjsHOYAzMHI3lgA1CYbbl6OtIQAnofYJhoAgje3APSPewDqmHsA7nS0e15KewICDwCj2VC8DEqAkBqD2aEhTAIjERHwIn1hVDOCQSmHQewSXQUADoHkiWAkDEjDm4COcccw2FcHuNiF4HHtsKokQx0BYmMgANYHADsVmFABFDlY7qTMOTKZhqWSKSilXTkWwiVqrnCDApQR5BEwpmRAeqGZgtUTsPQ2IIFEy7iy2QQOVzXHzBdTDTUTdSbXLGARidqNtcww8TKKHntY4C5SqqUdafTWJatdgecFgA6I3c438UkY9gBZTx4w7ivY%2B40hYj%2B21BkNE0gcrNGZtMjbS%2B4SqWRu7KhVq1Oa0PXJ0EVnstxMBIKLz0fsywcJ4fJ81pq2O27O9kAFTpeFEtAAYliRWLJd2B7ch6qN6OPqe8MRxju967Dwlj2Jz3gEmpF83wIHcox7At/mzM0cQODYq1nedF0VI5gPfCMbxlPtMPuVd5QfGlNzYPY0IIVsUw1D4hAqAR0A/KcXT2b9fzPLEgNfcZW2o%2BE6LzXsILjKDiwouCELnBclyObjaNbUiux7KNrwUvDExQwinxIjiyJgyi9mknlyKI9MiQAeSBaJcwnXcGIPI8T3/QDUK0riaIMvYzIQCztz48CY0EotgB00S3W5Xl%2BQFEddOY%2By2KODyvPHEAQAoncCyS%2B8kVLctqX09BZK0%2BTI2w5SngAKnKirKseB5Hgq/dsCEfcKuqu5asq9qWtw%2B4zC2SFdg%2BakTjoC4wJU9d1Mo7yrM/atxOQ5cuqEwKhC8bFklxAAlTAJNdStZqQyS3GCAhytbY7Tr2c6zsEQqV1uJa9i2nbguiv9YqOwRrpOr6LvO0qd3S9UFuZGpHGQAB9Jh9WiAgIHGdAkoUNNIdzNwVrWpR0CexdtOx2hQLDOYpQ4BZaE4ABWXg/G4XhUE4NxrGsPYFCWFYBp6nhSAITQSYWAUQHJswiWFMxJAADjF8mNAATkFjRYjFjZ9E4SReBYCQNA0Uhqa0Ug6Y4XgFBALXuY4LQFjgWAYEQEAlgIBITnISg0HJOholCNNOFUMXYgAWliSQ9mAZBkD2KQiTMXhcUIEg8AR5p%2BEEEQxHYKQZEERQVHUM2dD0T5iDnTgeFJimqZ5vXOBMk4HddVAqD2b2/YDoOQ7DyQI72CAPFd%2BhiAODm5l4U3zdICAkBdn9e6diAJ7dmJgCkMw%2BDoJE30oCJy4iYJanOIveC35hiHOEyIm0CpTc5l27QIEyGFoXec9ILAIi8YBZ1oWgjZpp%2B5UMYBxEfvgYg588AADdtrl0wKoCoJw1ic2Oq0cuZwIgFyPh4LA5cpx4HVt/cBxAIjrXFL/IwZwjA8wWJiJgOYABqeBMCfBMvSPe6dhAnlTtIRO8glBqHLroZoBgyGmEsNYfQeAIhG0gAsVACR2hf19vDSsQirCWDMLrVAeDiBxwgZIlobQ0guB5CMJopBAhTCKCUbIyRUgCCMZY3IaQejmP6GMVoICBCdGGJ4RoehyhQg6BMRxfQYhjAmLYkJXRAkzGCQsFmyxVgSBLhwSm2ty76wbj7f2gdg6h3DmYTuuAY5902FwQeXNyELE8kwLAMQIB8xAJIDYRJpYbGFJIDQkhRaxE1uTWI0tlYcFVqQdWGwuBEliFwBW0sxYTPJpILg5NmnxB1rTTghtjZlJzhba2Y9bbV0dhQGeqAe7u09hwWoLBQHCl9kwXUf8w7SyJKM3W0ciCaPjiw5O4g06cMzjwx%2Bugl750LjTRJyTlkVw4FXe2Jw9h1z2Ocy51zbnFi4A8p5ndu6T2iP3DYZhSnDxJqPceRysVkAObPXuIAEVXJ2H/VFXAtY0HxhZdem9t5H2YQfHeJ8z4OGYVfIMt977l2fq/d%2Bn9mFYBYH/ABusgEgPAV/Z50DkCwOYQgsmj9kGoPOOgtYussE4M5ngghSgiHSpIdmchfADA0LoQwph39OGfPYSw352ddYAv0H/FAjNLCiPEfAKRMi0hyIUfBJR1hVG0w0VoiRtTdFuL8BAVwYSTE8kiRY5oORrHpC8aMRIVj2iZucYmvxHj6j5uMb49oFaS3BMGF0NN4wIlmKCQkxYcTU6grLo/NJ1KkW0pRWiokGh8n4FeTikpQ9ymkEqdUygiTBnDIee04UCzhTCg2B0yQAdmjgv1msk21rLY2ztjXaeFKTlsE4Oc5uLAFCgNDqA1FRIFTjCjhO2O7znVsIkBw2Q7reEgCVkChIe8e0pL7ZXPZtd653sDg%2Bp9ewX0PPfa6LuJK544o2Pik9xLjlkudlhylT7sTg1Q%2BDdDkNiAsADsvZla8IAb0flyjl382PH1PufflRzr5CofnKzAL835iAld/KVMr9W8HlZURVkCVVqu/hqpBYidV6swZoo1vATWEOIf/K1mybVUIULQ%2BhjDGDMN/Snf9bruEetzkrARxg/U2GQfG4NsjOCPHhr64RKi1GxqwB5st7QDHuCrf4DNbaol2NzWmnNxaYtZtC1UUJkWXF6PcQE5LpaW2eMyNWnLhR20lM7WzDtmqwWpM4PC2j97H3Ptfeh8dhSp14c2RUzAVT%2BgJs1cukAZgHkbA2OTKWczNYjeFArKDajVm2HWQSuYdTJDCgjuurgUhpZruaVwYU/SNi9rmwbDZ5tEmR1mysk7S2Fh4JSM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/turn_over.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/typical_turn_over.test.hpp)
