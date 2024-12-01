<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::BindBack`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications-4">To Index</a></p>

## Description

`Roadrivore::BindBack` accepts an operation.
Its first layer accepts a list of containers and returns a function.
When invoked, the function adds the containers to the end of the argument list and instantiates the operation with the result.

<pre><code>   Operation
-> Containers...
-> Arguments...
-> Operation&lt;Arguments..., Containers...&gt;</code></pre>

## Type Signature

```Haskell
BindBack ::   template<template<typename...> class...> class... 
           -> template<typename...> class...
           -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct BindBack
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will bind `Con_0, Con_1` to the back of `Operation`.

```C++
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

template<template<typename...> class...>
struct Operation;

using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

template<template<typename...> class...Args>
using Metafunction = BindBack<Operation>
::Road<Con_0, Con_1>
::Road<Args...>;

using Result = Metafunction<Con_2, Con_3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct BindBack
{
    template<template<typename...> class...Endings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Containers..., Endings...>;
    };

    template<template<typename...> class...Endings>
    using Road = ProtoRoad<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJL%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW47eweYRye7%2B0yHxwQAnqmMrJgAdB9H2ADUyAYKCg%2Bby%2Bv3%2BCm%2BAHlnsRbtkviYNABBcbELwOb4WCLoCxMZAAawRiJMAHYrEjvhTvqcbncrmdbhd7k8XmwgSC/kwAUDsAx8EYFPDyZSUWiCN9lMRUEQAEqoJjoQmU74ksmIpVK6nnS6ahna5nMVmfQI/Dlcj4eQRMCIJAXGxXqileTJGb6y%2BXKwIAEUh0NhAkuFua1uIgI%2BpG%2BPL5wFDwLtgVVSpJnqOqvtFJ1tIzjJO%2BtebONoM5McjEWjgrVlKdpddcvQHu9EqlqDdCuOJf5%2BewKcJSe7SMJAHoAFQj0djgeD0cAFWwQino4nSOHY5Xi6J/bMgQify8WA9bjQDE2qQItq7/aRWb1zwN7yN5%2BRBFR6ItAH0NH314ir0yb3n74SIovgIr5cJ%2BhI/jmf6GrGD5AWKb5mOBl7XFqv4snesGAU%2BorfG%2BgTId%2BqG6vcxGZrmMHsmCnbYc%2BYpQgkfoMIRVYukIXipEUmDoNKmAKF4tBikc3oMTCDQBiBZjhvh0kgRoskMKB8Lxj2KH0pmZHZo80GYVRRZAoixBlnaSKscA3wALKYM0VBeEeDT1hiWI4vilyiUx5YgCALYSYp8l4SBYEmYiXk%2BcchnRjRKkXoiZmunxAlCV6lnWUwtn2XCxyIQpr4EXGqZIrMjjIK%2BRYJAQEDjOgXkKK8pW2m4vH8YJ4bsZxGTcU1iVfEsKYcCstCcP4vB%2BNwvCoJwbjWNY3wKGsGyYMqm48KQBCaP1Kx4gEkhvBokhcMSgQaP4GhmAAbGdZgABxXfonCSLwLASBo8mjVopATRwvAKCA8lrRwWgrHAsAwIgIBrAQqReAQ5CUGgex0AkUSvJwqhXWdAC0Z2SN8wDIMg3xSG8Zi8NxhAkHg1VcDIggiGI7BSDT8hKGo62kLo1MAO4wqknA8ANQ0jWzn0QtDUNiqgVDfGjmPY7j%2BOEztZjfBAHgI/QxBLYEXBLLw/2A6QEBIPDqSI2QFAQCbZsgMAUhSTQgk2pQsRs7EEQtA8fO8G7zDEA8EKxNomAOF7pDw2wggQgwtCewDvBYLEXjAG4Yi0D9Y2kFgLCGMA4hx5neDEMHjgAG58WzmCqMH0NbCtEQ7IN%2Be0HgsQwn7HhYGzT54E9Gdl8QsQdZ6uw583RjrSsVAGNGABqeCYJzDGjSt/C06I4iM6vzMqOo%2Bcc/oOcoNNlj6C3P2QCsqAntk6cY1VwmmJY1hmO9qD98QlPlxf3TF9kLi8lMPw1MwjWgWCMamRQsgCEAXoSBDR5jDESNTOwv8BB9EmJ4DoegUEOF6BMAYoDEHYPwTA5B%2BCEGVHASsOa6xNgSAFhwYapA3rjU4NLdGWMcZ4wJkTZWEBcDk01uYbWutVoTxWAgTA8oRgQE2kkQIbwACcgRiSSD2mYSQZ0Xr%2BDOoou6HAHqkCetrN4Z0uBnSuooq65j/D7X8Mos6zDhacG%2Br9MRccgagyNuDMW0NYaW1QOrJGKMOAtBYCXYkGMmCFhdFwRRbwuC7VJvgIgH8qZMzphvaQW9FA7zZroKS3MmC8zGgwphLCPqcFFpDaG3xJbfDCREqJMTzJxISbtFWatTYay1mYUR%2Bt%2BqG2NoE7pCR/FWw1iARpkSORGDiVweSDsdghmdq7d2ftQ4%2Bw9gHIOIcM7h0YAQKOMc2YJyTinWgadQ5Z1Hlsd6%2BAi64LLund6ldq47FDvXOobNm6tw9h3O5esP69xWv3QeShh7ZyMGPUAHi%2BDTwUHPBeS9Q5b0yQzbJshcmsz3iAKSBhx6PysCfX559ZEfWvgIW%2B98vREufq/d%2Bn8yXULqKgvwEBXCkJCLyChiwIEZCgTkTB%2BR%2BXFGyLy8BP9cFoJIcKoBUqGjoIIeUIhZD%2BhctmK0CVSDqHzToTrfR5TnEcAacQcJkTomzNafExJGgVYCNSVrHWetxGkEkdIxI5LG6GOMfEvaxJ7HEkOpIDR2NqYVM%2Bq4v6E9DZeKQBDcW4yRlm2RmwTgYS5YsAUCXAmJc2nnHGMkwRlM9BovXhipm2Ld7vV0MEIpJT%2BaGqFvnEWviJZSwzTjLNObvh5viQWsUqtk09OEYEfpMbvETLGRbKdiQc2cVfH218A7SpmuxnwOgyyfoQBdvnLZGyM77v9oHYuocDmR2jrHe5mBE7J1TunFaNzoWAoLo80u5d85vOQDXT5ghvlNxbm3B4AKu7AtDmCoeI9oWlhjVPJgs956LxvKi2Q6KJCYsEFW/JIBggEuMMfGwpL4CX0pQwdOA4qpHyfpYF%2B41GVYGZQqv%2BHKAFyr0CAlVlCkFpAFQ0LlcDxWEK49g1l0rGiyryPKnBiryFCb5bYCTWC1Vark1Q1YtCGZlOba/Nhnbvjdtzfmhk4x7UpJIE68dHiJFSKwJ6hhPq8XxMCIEfwJ19ovWc8SCxTiW0uNsG4gZSw5HJCUf4K651FGSEUYdFRXBcOcECNp1hX13GAwYSTHzOmUuBZWP3TIzhJBAA)

## Links

- [source code](../../../../conceptrodon/roadrivore/bind_back.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/bind_back.test.hpp)
