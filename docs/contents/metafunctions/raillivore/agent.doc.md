<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Agent`

## Description

`Raillivore::Agent` accepts an operation and returns a function.
When invoked by a packed stockroom, the function extracts the list of sequences from the packed stockroom and instantiates the operation with the list.

<pre><code>   Operation
-> Stockroom&lt;Sequences...&gt;
-> Operation&lt;Sequences...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<template<auto...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Carrier<Seq_0, Seq_1, Seq_2>`.

```C++
template<template<auto...> class...>
struct Carrier;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<template<auto...> class...>
struct Operation;

template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

using SupposedResult = Operation<Seq_0, Seq_1, Seq_2>;

using Result = Metafunction<Carrier<Seq_0, Seq_1, Seq_2>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Raillivore::Agent` uses partial template specialization to extract sequences from a packed stockroom. Here is the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
    struct Detail<Stockroom<Sequences...>>
    { using type = Operation<Sequences...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJLBAA6oCoRODB7evnppGY4C4ZExLPGJZly2mPZFDEIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW151WN9A2UVIFUAlLaoXsTI7BwEmCwpBjsmgW47eweYRye7%2B0yHx0xeRAB0L0fYANTIBgoKL09vn2%2BCneAHkUglblk3iYNABBMbELwOd6w4CMAgw2EmADsVjh7wJ71ONzuJwAnuDmGxofjCQikQR3gARTBNOjvHFWbFMo54rG0gnE86XIW3C7HUWkh7PV6BD5fJg/P4AhU/d6NVDIADWxFQqBYpCJ12F90eqGVcsBit%2BLyEmAAjl5GJsFDTYYT3vTkSy2bRLhrtbr9f6HU6GC6Ldg3R7Oe8vBkjESKZgOYEmaDwcRIQIQ47nZgbf85byOdzeZiYwKjWcxSLk1TMH9UcRMLt0a7i1X4xFgO8ALKedCp9M%2Bph0S7N1tsQSFt4gEAEZPluE4nmBPmYgD0ACpd3v9wfN1v9%2B8ACoFgjA/dHuE7g/3vc3/lYsyBCJfLxYVNuNDhzApS83UxSVxSuGspTNSMrSVWUozhL1GTcZpiDwBJl2fEDLmlc1YMxBD1QdAB9DR0OA41a1NGUizg%2BECERZE7XtQiuFIuFMMonDqLwuiGQIpizFY2F2LAklQOwqDVVnTtaPoxkwQhepBOExdKVYRsXlhYhgA7Gju0TPtWSYKgvHDephxRNFBEueSs0UuV5wHWh0AnLSpKjddMUxPTeyELwUgKTB0AAJQLLxaEZI50xs7MGFzYjDUY5iEqIgTiw8lc4W894QoUMKIrTftDOM0yoWOJDiBQtDjkSjRkqY6o%2BMI1L3Pcjd4KaRxkEI60EgICAxnQecFDU7qOzcHK8oSvyAuC0LwreJZeQ4FZaE4fxeD8DgtFIVBODcaxrE9NYNhTcxAh4UgCE0ZaVi1AIADYngADnuqR/Gxe7JAATkCD7X30ThJF4FgJA0WrNu23aOF4BQQFqq6tuW0g4FgGBEBANYCBSR5yEoNA9joBIojUzhVBegBaT73mAZBkHeKQnjMXhAsIEg8EG6p%2BEEEQxHYKQZEERQVHURHSF0aoAHcsxSTgeBWtaNuunbOBBR5scZVAqHeMn7spyRqdp%2BnJEZ94IA8An6GIDlXy4JZeARrQVggJB8ZSQmyAoCBXfdkBgCkMw%2BDoHZiFhiBYiV2IImaMlZd4SPmGIMkQVibRMAcWPSHx6cCBBBhaBj0WsFiLxgCQ2haFh7heCwFhDGAcRC7wFsHDwAA3AslcwVQ08eLYLoiHZVtF2g8FiLNE48LAlbovAQar0h2%2BIWJ0kwFla6MEejGulYqAMbSADVUIl%2BTNournhFEcR%2BfPoW1CV8X9DrlADssfRR9hyAVlQACskr8mBsiqYSw1gzCQ0XihLAH8IArDsGneoLgGDuE8O0PQYQIiDHKMMaoBRMgCEmH4bB6RcEMDmEMRI0xahwJ6OMVoyCphdCoQIXoLRSGYPIbYGh%2BC9AzBYeg%2BYWCYHHU2BIeWHB1qkAhrwKG2sKZUxpnTBmZhTa4FZlbM6tt7bbxWAgTATAsCJGgaQO6yQng/WxJIDQkgzCSHumDfw90voAw4EDUgINzpPFevdJ6X0npcHuv4SQXB/A/XuhIpWUMYZw0utvZGaNnYYzVjjT23tLbEzYJwZoLBW7YnJkwK0iYuBfSeFwJ420WZEAgXoc%2BPMr7SBvkoO%2BotdABylkwGWVdRHiMkcrDgqssaPHeJrd4mTsm5Pyb2QpxTSmm3Nm7S21tAhmDttExGTsXb6jmQkXGXsNk%2BxGTkhURhClcFqjQcKCRQ7h1FvHaOGcbmJ2TqndO88s7olzvnJWRcS5lwrhnGudcG7bXwM3Rw7dK5lO7sgXuGcB61CViPMe0dJ5bG2jPOeF1F7LyUGvAFPYYm7yYAfI%2BJ8M7VMvnzOpshb4i22s0x%2BW8gFWFfgiqBX8f4CD/gAtMjKQFgISBAjun8GEt2cBAVwXDqhoNKGQ/IRD6gStIDg%2BorCFgUO6EwzhdCCHCvqMw/ofCZXTE1bkbVPD9XSrYSI1Y6xhG2ycV08JnBhnECyTkvJhyJlFJKRoZR%2BAKkLI0Ssx22jdH6MoKIlxbiimWOxME7E2JAhWJsYEsJosIm2CiQ7JGKN0aY3VtslJRMSYcEyVTFgChW501bpM84YxmZ%2BrZhzAWF9eYSEpYLBpNKdAgGCK09pct7WKzTSrRJGstalv1uWyt7xq1FNrYyM2uz5lnUCMsrNayUBLq2ckrdiRK3%2BUIrOwi87uous%2BoHc5IdKBXO2vcguF072PLgRnV5gh3kFyBZgYupcxC/Pnv8jeKLq5NyoWCzukLoXz1hUPbaCLx5kmRdPFC6LeCYpXjijeeLVl8D3goQ%2BmBj6UlJbIGpFLm3Uvvj2%2BlxgX42BZfANl9RK6bgGs/YBlhQFSPAezQVhjYEir8GKxBCqpUYNVYquVWQFVKqyCqrBOrqF9AVfx3VNC5PsLNcptTBrLV2oUEIvmnSh2QydRO94U6q01rFGMX1qiA1rq0aQHRejhiGKHpGxYRTAiBH8P4SxJyNDeY%2Bk9VNJnoYZvho54xgRimBCegE18fn7qvg%2Bk4wIxmpGcE0as0RTNQuZfC%2BulYi8MjOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/raillivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/agent.test.hpp)
