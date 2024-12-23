<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind-front">To Index</a></p>

## Description

`Mouldivore::BindFront` accepts an operation.
Its first layer accepts a list of elements and returns a function.
When invoked, the function adds the elements to the front of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Es...
-> Args...
-> Oper&lt;Es..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<typename...> class... 
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct BindFront
{
    template<typename...>
    alias Page
    {
        template<typename...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `int, int**` to the front of `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** Supposed Result ****/
using SupposedResult = Operation<int, int*, int**, int***>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = BindFront<Operation>
::Mold<int, int*>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int**, int***>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJJmpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJkCbhBYLemEh0IAnqlGKxMAA6TGQ7A3ZAGBQKG4AeRRxDe2WxQPGxC8DhuFgi6AAYsRZECTAB2KyXG68m4wp5whEEZGotiY9EWTDACIMCLABSUnl86m0gg3ZSsogAWU86CBfJunO5F0NhoF4PhUJFKOY4sx2GejAIisC2ANZt5XkyRhuuto6CNgQAIsTSeSBAipTKGHKjAoJaQbo7Qc6E1i3ZCTYbOcGs%2BzlbyLULraK7RjMdHZfLXe7CzdvfK/Xqg6HNagdXqo9Lq/GJZTAibc/nLkCfn8jgDx8nVKwnpgPqcxxP/gXAWZAhE8V4sEG3GgGJtUi6lYDvocwwkIwxF/sAcWIaXbWj%2B5nLqq6SSrw0R2erhehC8VIikwQMACVMAULxaHVT4gUbX1AOAjJQIgqCYNbS8yR/KEIgIJM8N2AjBH2YiCAOAch3PW5tUwZoqC8Q93jgy4HytJFn3tdELmIBVTwQ4A/TopgGKY7JMIZBhmVZQQES/bCKTfC4QBAf19VwwQyN2U8VLUhEeIVV93UHNdpzQ6DYKXS4BJucyMMhUNaPoxiHEUtxCKIm4PO0zMTNHaj9huAAVSDLLvKlmkcZAAH0mAJBICAgcZ0BUhQ0Vi103Ds/CbiQkD0Gy7ElizDgVloTh/F4PwOC0UhUE4NxrGsG4FDWDYF3MQIeFIAhNFKlYAGsAkkdENEkLgOUCDR/A0MwADY5rMAAOJb9E4SReBYCQNA0Uhqtq%2BqOF4BQQF23qatK0g4FgGBEBANYCFSLx8IoCA0EeOgEiiNFOFUJa5oAWjmyQbmAZBkBuKR0TMXhQMIEg8BSrgZEEEQxHYKQUfkJQ1D60hdGRgB3MlUk4Hgyoqqq8cOolnqe9VUCoG4/sB4HQfByGRrMG4IA8D76GII0Ny4JZeHOrQVggJB3tST6yFemW5ZAYApBSGgYISE6IFiPHYgiFpETJ3g9eYYhESJWJtEwBwjdId6XgIIkGFoQ2LtILBYi8YA3DEWgTu4XgsBYQxgHEN38GIa3HAAN0gvHMFUa3nq2bq8LqPHaDwWIyTNjwsDxghiDwLaA9IWPiFiFDg1BEPM6MPqVioAwFQANTwTBCa/aruv4VHRHETHe%2BxlR1Ddgn9BDlAmssfQs5OyAVlQY9sn9gHkoc0xLGsMwDvLousHniAVjsKPshcKSpj8ZGwgiIZKhGZGiiyARL70J%2BGnmYZEmRk/XIEPpJieA6HoX%2BDQAEDFvgsB%2BtgJhtCAfkH%2BsDP732/sfNqmwJAUw4JVPa1NODM3%2BkDEGYMIZQ25hAXA8NBadRFmLBuKwECYCYFgRIR9SBDUkIEdEABOQIHJJBjTMJIOaO1/BzW4WtDgG1SBbS6uiOaXA5pLW4UtRR/hxr%2BF4XNXBbtDrHVOj1BuV1bpS3unTZ65BKCKwFt9NgnAWgsGjhyAGTBcQGF9Fwbh6IuCjVhvgIg%2B89BDzRgPaQQ9FAjzxroFIxMmCkwDlgnB%2B1eA03MQzJmLMiFuJDpDLxPiNA8z5rLAWQtAhmFFoYi6ktpaoH5gkSxb1anFJGHiEOniuC7XViCYgWsdZuxNgbW2AyzYWytjbUu9tnROxdnjD2Xsfa0D9rbIOtcti1QjqfWO/taoJyTiCW2adypu0ztnA2ec1liyLiXbq5dK5KGrsHIwddQBVL4M3BQbcO5d1tsE/uGMwmyAibjMeIAUjuOMNPGwJzD6L2XgIVe68QybysJYHeKS96Izjgvbop9nAQFcK/a%2BUlkGLEfhkZ%2BOR4FXzSOSj%2BkCv4gLqLixosDCU4r/iyuY9KUEgNZVS3lXLygMpFqsdYGCRVHKSXgjgBDWYg1aR4vJo0eaUICaU2hlSJYMKYSwygWDpGyK8WNDkmiOSTWSMI8aOiDqcH0WdIx107oPXpg06xX0focAcWzFgCho4Q2jp49Elpxh%2BKoYjIJsgQn/KxkC0etVdDBFifE8mkipW6M4LTR6z0biM2Zt631/rA3BvVLzJpctSmBAqeLS6pi3XyysWWgWIA/XAWigG7h0Vi3RVUMDPgdBum9N1vrM2Qzh3m0tlHW2kzBDTNduszAntva%2B39t1FZTyLnuzwJHVyWz46J2QMnA5gh07HKzjnRE5yC5XNtrcquNcnnyiMU3Jgrd26d1tD8yNfyJAAsELGqJIBgjgqnlvGe0L4CwoaP7bYyUQMoosGiuqGKD4QfZQ0c%2B7h%2BVEvQCS6B79shsvw6UblpK0O9D5XkaloDyOCrvqR2YgDKMCtaLh1Bor2qYNTVTdNMqe0gx9X6m47ag1wnGCq/xJB1VVvoaQRhzCRhsKOQa0FXjAiBH8DNcaO01MciUdalJtrbAGOrUsQaSR/A8P8Etea3DJDcMmnwrgQHOCBG4zao6mr%2BqSJhvpuqhmTMrHLpkZwkggA)

## Links

- [source code](../../../../conceptrodon/mouldivore/bind_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bind_front.test.hpp)
