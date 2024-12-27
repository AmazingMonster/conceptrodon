<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Reiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-reiterate">To Index</a></p>

## Description

`Varybivore::Reiterate` accepts a list of variables and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Shuttle`.

<pre><code>   Vs...
-> N
-> Capsule&lt;Vs...<sub>1</sub>, Vs...<sub>2</sub>, ..., Vs...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
Reiterate
 :: auto...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Reiterate
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will repeat `0, 1` four times:

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = Reiterate<0, 1>
::Page<4>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Reiterate<*>::Page` is implemented as a shortcut to `TypicaReiterate<*>::Page<*>::type`:

```C++
template<auto...Variables>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Variables...>
    ::template Page<Agreements...>
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcAGykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxuxzuQgQXgIBHo3yOwIImBY6QMSJMgTcTGhqAAdPiMdhQZNiF4HBCoTD6BirNdQf99ndsKokQx0BYmMgANbww7A3a7O4AdUwdwA7nRaHcvEo7gQEHgvlQvAwHLk5ah6YK0KqmKy9aL5aL0sRPgkAG6YdB3QzW03ITZKa3pQYKXGgpEotGYDFuAgATxezDY%2BPdgSJ1xJZIITJZrg53LuJgA7FZkw8aaCPcjUQbfaC7oW5Tnvb7sURQ4S7sgDAovkJMABHLxvTCkAtF8t4/EANTaeCYsXoCiz4eJBFJ5OZrPZnK5vobzdbvr7xAHQ8%2BlbHY7pqY7hc9ufRmK7oauwFNyMYBBHO6uRel2SMd2UTGAooxDwhTZbqp9mNXddh1DUg7nPS82EEN0CW3WkQXTTM6T%2BcEABVAzwURaAAJUwQgEgNXlzmzL08xPHFQ0Awdh0JcdJxjND0gwsQcLw4g813OCH0PUsyIrGCI3vIso3JZRiFQIhX3fJM9wQwI4K1O4OVlLElBAfdixI48sRxO4AEkaOuB9TWbPBTS%2BCBdKTQIM2su4NBWdThJjUTxNQST/zcfS7wfFNOIfIsZQiYA5UDD9bMhaFYQ8mi5PUlMbPkwyi240jtKIPSDMEwtjK8UzPjuCyrJsr8uAcpLCycl8xIkt8PK8gSfL3cr/MC58AxeIqKUi6kAP7KjN34xCsukhKsz%2BQUcIdYhsktO4VPYdSUq0rsMu8oscry8yzCstxPz0srhsqlyavfX16riprhofVrgvasKv2neM519O7g1FY63Nqs67gAWjuMxCRAEA7sy/yiyBpb3q%2B3q1366DcVAyiN3hmK/MLeKhsWktUtPfFwMwK8oNBgKn2C9zOo%2B9zfXxwmby3IlYt3UakLBQE2Z%2BelwV0r1ab1dUOeQ9mheBYijw83HcSR6i70qlikTY9EOKxzTxfIvGLwJyCb2JwsbpfWrOoYpjsNw%2BXUqlgawwa8HgexpF9dOzEaa1lG1sLCHQsx2TEtZoWEU5%2B5mVYVFRQF32/aIlnzECCIay8LAdp1bZ0m1u8A8OLqqVD/3rkhss1at2jo0zqLMcFjOhC8dISitHCFC8WgYzDvXK%2BrrJa8%2BBuYz2iKs/zZqNFArh2wHoeR%2BGwe7mH9TJ64UcGZ9hk7jrrvCOBPWV8bzq5fwrTZ8yoGqcxSRUbG8O7hQz4m5zq55kcZAAH0mDrBICAgSZ0CBhRWEwJ/bzcTeBBQKtxrugQBhIHJyQ4GsWgnB/C8D8BwLQpBUCcF2pYawdwFAbC2B%2BMwgQeCkAIJoaBawuQBEkLiDQAAOMwZgkhJC4P4Gh1CuDJmTNIWBHBJC8BYBIDQg9EHINQRwXgCgQCD2IUg6BpA4CwBgIgEAGwCDpGhOQSgaAUR0ASFEH%2BnBVDUJSD9FIkg7jAGQMgKelCzC8CtIQEgeBP7D34IIEQYh2BSBkIIRQKh1DSNILoYeYo2LpE4DwGBcCEEkJQZwAA8tCVRMZUBUDuAYoxJizEWKsbibaEAPBaPoMQJM%2BDSq8CkVoNYEAkCaMYoU9REAanaMSMAKQZg%2BB0HluIiAsRomxAiG0f0YTeB9OYMQf0sTYjaEwA4IZpBNFa1iQwWggz/FYFiF4YAWJaC0HEdwXgWAWCGGAOIVZeU1SWl2cgzAqhpnQh2IQiISIuHINoHgWIbExkeCwNEiceA%2BF7NIJaYgsR25PEOUYV5RgSFrCoAYYACgewfDFLEoMsyXHCEwh46Q6KfFqGiYE/QRyUDWGsPoN54jIBrFQCnXIuyfof0/KYDBlgzDCKBWuLAFKIBrDsNMpoLg2QzD8MPMIEQRjVDGMPEoOQBBCr0NKpoixRiJGHrytUAgBjTE8F0PQaqmiaqGGKpYkrbBTA6NqwoqqzVKolSqnlODtgSAiRweBpAhG8BEakwxxjTHmMsVIHJBVcD2KKdHUpRDoVrAQJgJgWBEjctIOQyQgRcRJECBwjQkgzCSBSAI/wKQkj6E4Dw0gfCCG4hSFwFI1CkisJSP4SQTC01pHdTE0RtgJERukZUhRVSlEJLURQBpqACk6L0RwNoLBzTJh%2BkwasBhnxcCSLiLgVDbH4CIByvQ6K3HiE8TipQeL/G6DacEpgoS9nOtda2kR8SVHQjuMkr16TTE1iOVPZdq6NAFXybUhIxTAhmBWGU6Fsjqkjr/WQIdjTCkoAXS0xhg8aCNwSF0np/iRkDNmZhsZEypkzIBfM68izlnRLWRsrZOzZkHKOSc5B%2BB7SOAudE65tykSzMeQ0aJrz3kDK%2BTsZBvz/mEKBSCpQYLaNBVA7Ct8CKkUosYGi2Qu6sVePkIevxyCT2EqhUyqwlgyWxC5VSmlAg6UMusnp6wrKPXsscZ8eAPKGh8tyAK9wFrhUhDZDa5YUqsgyryB5%2BV/nFVGuVbq5z6rmhmrlaqyL%2BrrVhdtbqmLQWrULCS75%2B1mxHWlSLS6qJ/jPVpJ9fO99S6V1UKDRukgAHw3lNIaQaNsaxgJq4SWsty7M3Jn8EkdhgQs05sbW66JIixGdoaz2%2BAfblGJPqTBsdbBOCToySwBQ5pLHmgq96SY66Q2OO3cpzFEhsWyFxZpnQIBghnoveE/L17RtxIHUklJqhVvrc29tg0kwf0QaaQBwIwGu0VLAygP7dToPg7GBt6uD8ttJAfjtggD83vYo6ahyg6HkE4ZWYQnHeG%2BWzKI4IEjKz6OYHWZssQVGAU0YhQJ/ZZymMOf8axh07GAWceebwHjHz/T8Z%2BWuYTvBROguRJJqF3a%2BBwrk5gZFqKAU7uO/us7Gn8VXZ08YElBmePGZQaZhguzdgf2JcyiwNmUF2c5Y53oLnnAQFcLFrz6AfMmoVbkJ37vyiZZNXq/oqWCieb9xqxLlRwvpa1YHlLGWw/Jby9gnLHir2FeEZwVJ72Nt3Hh7iJH1WQ11aB5NqNMa42UGdR1kA9DcSBECP4ZhjaBE1%2BTNWkbRXODjckZGxNIBJD%2BFTWw5MAjqGSEYVwWhZg0hcMCCnj17fgeNa4TY1vqf21F8Bah1zkggA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/varybivore/reiterate.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/reiterate.test.hpp)
