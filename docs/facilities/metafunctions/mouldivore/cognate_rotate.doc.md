<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateRotate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-rotate">To Index</a></p>

## Description

`Mouldivore::CognateRotate` accepts an operation.
Its first layer accepts an amount and returns a function.
When invoked, the function relocates arguments of the given amount from the front to the end of its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper
   &lt;
       Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>,
       Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
CognateRotate
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateRotate
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will rotate the first three elements from `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int, int*, int**>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateRotate<Operation>
::Page<3>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateRotate` using concept expansion.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct Swivel {};

template<size_t...J>
struct Swivel<std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        Prefix<J>...FrontTargets,
        typename...BackTargets
    >
    static constexpr auto idyl()
    // Note the position change of `FrontTargets...` and `BackTargets.`.
    -> Operation<BackTargets..., FrontTargets...>;
};
```

`Prefix<I>...Targets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADs/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWGkDMz8QRkc9mGxSLcsgAvTAAfQIZKuaGxTwIVJpdJhgXutwIxC8mFhViuIL%2Be1uQgA7ngAG71BkHJkstlMDlwrk81gawLoq4TNUOfVG020GFJKxJe6a8mXZms9lOtxC0UEAB0cYAUhLLm6vB7DSb6viiSAQBEsKoRUoAI7q6X4%2BNxmNk50Yv0g24NlVW8P1xv41uNxuh622tz2xiOyto26QpgKT4AeWexBtOVIHc7ctpeFU5bRlYAYsRZAAVVrATAEBTzq6LrvcgdsSsWJjIADWe%2BIB6PC6TnbmjmQI4EE0wqjSxC3EwCKoLceDoMitAQMsC47DstxRKgzIqggmC3MU2QCCOCCGAetyoFQMIAGwaFuu77oeChDiRQEMOgxEaDe96Ps%2BVEmCRVano2AC0w5Tgks4CPiTEPhRR6VvyZGCCxlFDjWgRasCAZBtqFIAup3w6pSACSYYsowLSNOaZxaRpZlAiC3YtnazY2hG/a8pgcnYCOBjjrc/Ezo0SYph6HjAMwzIAEpIXZtaKZ2VlhXCUZirclwsOsghvo2vmytSSGoMoTAHq%2BdZcWeUW9g5g5xtg9BsIICgpWeXhZEYtwALKePRsLKlgkL9gunYQN1Z6ehmtBZgQ6A5iwTB3qKeZ/oWmAlq8EYJUl4ryS6lz9YuOZFWh4GQfinmCQw/LlfpVXOdBfUNjBCl5YGN2qetXa2b2wFEJWlzADSp0vjWBW3HVETAFSOVoW1cqZdluVwh9X2VeJcbVopJjKfdwJqWZjKmQctzYKorBsmhmnoxjJkPZiEJQqDcJSlsaQ/WtWN6gdRlEyGz32RejnOSCaUedOh0qWj1yUkIXhpMUmDoEFHxeLQsqswDDWi%2BLmSS9LCiy7KYPMzk%2BIRAQBz8vrRuCHsJsG3siPBrqTWHkwVBeNiLOY1c22cpzpUxpcT7Vb9lyK0DjV2w7Ts5Iqyr%2BYFmAhYZEY60Jfs5pDEaBEmObNbQ6D4t7wBUQj8lI8Ttzq5rxlAgHxcy3L4e2y0IcOLrcLG2Bpvm4bLcW1bD02zuHzyy7yaGXgyAimOShtBA2YgAojqj77bgl3L/LKxLUtVyt2DXRYHCrLQnD%2BLwfgcFopCoJwbjWNYArrJsoNgjwpAEJoO%2BrHeASSDGGgABxmGYACcf8uD%2BG/l/LgSQkjSD3hwSQvAWASA0BoUgR8T5nw4LwBQIBEFP2PjvUgcBYAwEQCAdYBA0gInIJQNArI6AJCiI6Tgqgv5EW4kRSQtxgDIC/FIGMZheCS0ICQcCeh%2BCCBEGIdgUgZCCEUCodQODSC6C4KQA0M40icB4Lvfeh9n6n04BOBEZDZQEVuIw5hrD2GcNuNwswtwIAeGofQQCmIuDLF4NgrQqwIBICoWkGhZAKAQB8X4kAwApBmD4HQZkxAMEQFiDo2IERWjInUbwBJzBiDIgnLEbQmAHApNIFQuGE4GC0GSfIrAsQvDADcGIWgGDuC8CwONIw4hyl4BpA3U09ST5/lyQibYD99b1B0UiWIM4MkeCwDo1UeA4ENNIKaYgsRVaPGacAJERhn6rCoAYXOAA1d4Bp%2BJHwfiI4QohxCSLOTItQOjFH6FwigS%2Blh9B4FiBgyAqxUB0xyPU7iRI2qmEsNYMwKDFnEHAh8eAqw7C5MaC4Oi0w/BKLCBEYYVRRhKIwo0JFehsU5AWCMRISjYUNwEP0KYnhOh6FJY0Clgw0WLExbYSY7QqUFBJaywlGLiUwpvlsCQmiOAHyQTo1BJimEsLYRwrhH8bEQFwAIpx99XGPy2asVCTAsCJGgqQN%2BkhAgxj/oECBGhJBmEkCRDQ/giJ/30JwGBpA4GBC4DGIiXAiJfz/qAoi/hJBAONURUV8jUHoMwWqnBnjCFeOIQY8hASgmOLoWwTgrQWDGiSNxJgrlcJWL/jGV1PT8BEAhaNJRZyxGXOkNcpQtz5G6HCSopgaiGlCpFcg3gqD9GkIRPhQipipU5oalwfNhbbH2N8Y4mEYIzCqvcbgmNiaEgUMCagBxoxRxGBHVwRBNA5YJBiXE%2BRaSkn5JPRkrJOS8nzMKQZYppSdEVKqTU2gdT8lNNwq0k%2B%2BAOmOC6To3pyB%2Bn5KGVAk%2BozxnIkmdsE%2BMy5kP0WcspQqzP2Ay2XwXZCgDmYCOTyfJFaLkSOrbIG5ciT4NoeZsoFVgXmjI%2Bbq75jQ/kAqVNRkFYKEilqhZ8nocKcgIvcOy5FIQ6LcqWFizImFchCbxZJxoYnmW0r6Ky3FJL6h8fJVyxlRKaUqZk5y%2BY2meWCrWBsAVLj7XCu0SGzgEqzFsM3UDEdBbP62MVSW6dLq53qtIJq7VlAhWOudfms1KQ/7gMCOay1/rg0oM4GGrB6H8FEJIYYldS7iDJu2Gm8xLAFDGi/MaZz4YJh8OLYIstUjzniIkMR6RtayM6BAMEJtLaNGWfbWKvRcajH9ty/lwrxW7ITHHWuydCRPOBG85GvB3ixt%2BPS/NxxIACvixFEVv%2BIoSsEBFKoVhET93RMoEek%2B56ykPzO5euF%2BTb2CHvWU79mBKnVNqfUh%2BH6Wkwcae0vj/75GAeA/M0DIy3mQeg9MiF8HeCIZWSyVDmyZs7Jylhw5xz8OyErURqrpG7nNco8YZ5Ng6PQtPj8n8nAdjZjY5YUFnbwWQvozC9TZK/AQFcKpkT6AFPEvSHJnIHP8VlCM%2BJ3jLP6Uc6U5pwzFQdMGcpfkYTcw2jc5MwoflEi23WbixwEx/WCu3A2zGbbbnyvKq824nzfnRi6qgUFkA/8YyBECP4YB/qEFO6SJ62Lnb4u2HDfO5Yr8QCSH8EasBSQEFf0kIArgP8zBBqgYELXPu0ERo8UK3h3vdGp4D6sRZWRnCSCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_rotate/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/cognate_rotate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_rotate.test.hpp)
