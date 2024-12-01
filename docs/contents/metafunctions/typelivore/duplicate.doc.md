<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Duplicate`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-6">To Index</a></p>

## Description

`Typelivore::Duplicate` accepts an element.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function creates copies of the element of the amount and instantiates the operation with the result.

<pre><code>   Element
-> N
-> Operation
-> Operation&lt;(1, Element), ..., (N, Element)&gt;</code></pre>

## Type Signature

```Haskell
Duplicate ::   typename...
            -> auto...
            -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct Duplicate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        using UniRoad = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `int`:

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int, int, int>;

using Result = Duplicate<int>
::Page<4>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion.
We start with an empty list, adding the element while subtracting the required number of copies until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this by pack expansion.

We want to bundle the element and each index from a `std::index_sequence`.
Then, we will pull out the element from each bundle by a pack expansion over indices.

First, we need to create a `Bundle_t`:

```C++
template<typename Element, auto>
using Bundle_t = Element;
```

The entire implementation is presented below:

```C++
template<typename Element>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation
            <Bundle_t<Element, I>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQgZtIADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJSbaY9kUMQgRMxATZPn6B1bWZDU0EJVGx8YnSCo3Nrbkdo739ZRXDAJS2qF7EyOwc5gDM4cjeWADUJltuXo60hACex9gmGgCC27v7mEcnyKPoWFQ3d48PBEwLGSBkBxzcBEuyUYrFe2HobEEpAOTDOqF%2BDy86SMBwsXgY6HobwAIgd4UDGARjlYHn9AcDQZhwZDocw2GSEZSMfdRsQvA4DsSvCC8KIwbSAOw0%2B4HWUHekgphgk4smFsblyg68/kEA7KYioIgAWU86COUpMEuJ1L%2Bf01CsZ4PSAC9MAB9AgAOm9AEkNXLtQL9YbUCbaOgnQR0CAQOEsKo3UoAI5eRjrcE%2B72e35bW4PTWW6Wa%2B1AxXKiGlx0qqFqzBZm4HPZMBQKA4AeWhxCVmX9xa1BD5AuJmEadDtffNRYnmqx4WA8prJPbne7AnH09l4LxBPo4PJiIIyL9ufruZt%2BYnlutW2l6%2BLDqVTJVlcfzJrbLr3obTZbWfuwGITAKUEBRe2LWccQAJVQJgzWOUlh1HWhwX/QDgIIBRT2wGNVXPGU5SvPC7wfctVQ/P8AKAg9QLPC9ZQg%2BcwzgrZSWDY1TRQyj0Mwr8zxvW06PlF9yxdd1dWPPN8NlQNdTY1BlCYYAmUEkADmSLwYguZA9QNdjw0jaMQBYJgAGt3TjTAE2TVMGHTE4JLAwtCP42lBJIp83FRIgKLQ6iwIYvVFNeeCdJDBSlM43zKR47M%2BNvK0iIeAB6AAqNL0oypK/lStKABVsCEXL0qy5KMrKlKSv%2BR4zB2WyXjeU5ziubk6WEjyyNhLC/hk5d4lXBhEvuAKhGFApMHQSDMAULxaF1EKOz6upwXCQ8DhW5F1rWwQc1vTFsXnSbptmpchRFMUPJW7kY3CjzJCukBoNg8EFq7Ja4oEnlGkcZA3WbJRmggT4YwUWFfpotxDpm1aRuSMaJqmqGbgWakOCWWhOH8Xg/A4LRSFQTg3GsawtRWNZgpqnhSAITRUaWEyAjMT0JSSAAOFnAgATn8MwNAANhZrZ9E4SReBYCQNCCbHcfxjheAUEAgmpnHUdIOBYBgRAQBWAh1MPCgIDQYE6HiSJYU4VQWd5gBaXnJAOYBkG0qRPTMXhxsIEg8GjLgZEEEQxHYKRffkJQ1Bp0hdB9gB3Ltkk4Hg0YxrHw5ltszl1g5UCoA4Let237cdg5nbMA4IA8I36GII4KYWXgla0JYICQQ3kmNsh9ZbtuQGAKQzD4OhAWIeWIBicOYnCJpLnj3hx%2BYYhLjbGJtEwBxp9IQ2DzbBhaCn5XSCwGIvGATzaFoeXuF4LBjKMcQ9/wQCHDwAA3Kbw8slezg2SmVpqcOLhiLs88PBYHDgOPAYsL6kBfsQGIaRMDDmvsAC4RgaZLCoAYYACgABqeBMBRwWtjSm/A/aiHEEHYhIcVDqD3pHfQhhjBE0sPoPAMR5aQCWKgZIdRz5W0%2BPBUwlhrA814KgaBxAvav3YZ0FedQXAEgmH4H2oRwgDHKEMH2BQMgCAUXoTRdRZiDASD7OwMjuhjBaJ4NoegTGPwED0ZoBi1FGNsOYnRxjzGOPmFwJYChSbrAkInDgmNSBSxEZwHOlsbZ2wdk7SQLtS64A9lXbY3i66oKWAgTAsEhgQDpiASQWxPQcy2BKSQGhJBJF5hLfwvMOZCw4CLUgYsthcE9LzLg/MOYsw6f4SQXB/DFN5iElOnA5YKypqg1WGsm5a3TmccglBO6V1NmwTgTQWBPwlFbJgjYDA4i4BzT0rTcbuyIOI72wd/ZkOkBQxQVDw66D7jHJgccL6BOCaEvGnA046zOJnbO6zNnbN2fQouhzjml3Lq3Su1cthmFrhM5Wjdm6oArvEBZBtUXQqGICrZTYjAHK4EEGgs14jD1HnvWek815UvnovZeq9IEb0pFvHe4cD5HxPmfNeV96G31xvfUxL9z4nNUB/QEa8f7oz3v/QBlxgEbFxmAiBlNoGwKUAgvlc5JnoMUtg3B%2BDWRrwoVcwONzZB3LDjQxIdCUECKsEw/%2BbDcl4y4ZkHhfCWL2qEdLMREjnU%2BJqKY5wEBXBuOCASTx6jSB6MyOG2NxQVFzGjTYuo9iLE5EUdI2x9QPFJsMdY1xljcjuJmPmpxATlirH8d4%2BpHyRkcBRMQDZWydn4vnAco5noNAJPwGc2FqTEUNwyVkrACQXXSsac0w55SJQDIlBKLYFTJC2x9p8mWYzFaTLVprbWusMVLJNmbDg6z84sAUE/bST9O2MlGG7PtnsLkmtIWa4OlrqG410ILZ5ryE51uTnvVOczdRZybSwM9F6r03sfKMSFWK26wq2Ai%2BuKsZmHvbos%2BDlcQCXthm6a9HM3S3oIL9Zttt%2B6kqHpQCluNaW70pnR%2BlMi17MsEKy3eArMCH2PmIblkDeU30VZfPAD9HDCrfmK5An9JWCF/jKlhcqFWgPESq3gaq4GapvtqpFfAMH6rwQQ41shTUSHNYId9DyQCCz2QwwRjqWEBtddwzgSUgbessMIvGfqsCOdTZkOR7hi1ZuUaUAtGi0haKyEF3REX9Hlq8dmtNRbM3WKDTm9NUbnHTHGNF0tDj4vqJ8X4wO7yAPS3Caeu257L0HAI56YjvakkDuQ%2Bk0gmTsnjsCVOxIhythbH8IEPpEs%2BsSn5sMwDozbDjJQwsPJkgJQuznVwKQHNZ3FK4BKepWwythNlkO2m9TXbjfK3tmbSxoHpGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/duplicate.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/duplicate.test.hpp)
