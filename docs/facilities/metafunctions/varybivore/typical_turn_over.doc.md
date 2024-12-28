<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalTurnOver`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-turn-over">To Index</a></p>

## Description

`Varybivore::TypicalTurnOver` accepts a list of variables and returns a `Shuttle` packed with the previously provided variables but in reversed order.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Shuttle&lt;V<sub>n</sub>, V<sub>n-1</sub>, ..., V<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalTurnOver
 :: auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalTurnOver
{
    using type = RESULT;
};
```

## Examples

We will turn over `0, 1, 2, 2`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<2, 2, 1, 0>;

/**** Result ****/
using Result = TypicalTurnOver<0, 1, 2, 2>::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `TypicalTurnOver` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several variables in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

We will use `ExtendBack` to concatenate two flipped parts.

```C++
template<typename>
struct ExtendBack {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Endings>
    using Page = Sequence<Variables..., Endings...>;
};
```

Here's a simplified version of the implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...>
struct TypicalTurnOver {};

template<auto First>
struct TypicalTurnOver<First>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second>
struct TypicalTurnOver<First, Second>
{
    using type = Shuttle<Second, First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Page<Second, First>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxuxzuQgQXgIBHo3yOwIImBY6QMSJMgTcTGhqAAdPiMdhQZNiF4HBCoTD6BirNdQf99ndsKokQx0BYmMgANbww7A3a7O4AdUwdwA7nRaHcvEo7gQEHgvlQvAwHLk5ah6YK0KqmKy9aL5aL0sRPgkAG6YdB3QzW03ITZKa3pQYKXGgpEotGYDFuAgATxezDY%2BPdgSJ1xJZIITJZrg53LuJgA7FZkw8aaCPcjUQbfaC7oW5Tnvb7sURQ4S7sgDAovkJMABHLxvTCkAtF8t4/EANTaeCYsXoCiz4eJBFJ5OZrPZnK5vobzdbvr7xAHQ8%2BlbHY7pqY7hc9ufRmK7oauwFNyMYBBHO6uRel2SMd2UTGAooxDwhTZbqp9mNXddh1DUg7nPS82EEN0CW3WkQXTTM6T%2BQEUKBelwQASS9K9BD1dUfnQ1CiOBbMvTzE8cS3CMrijckABVAzwURaDozYGAAeUtYgkz3BDAjg0ij3/LEcTuAAxPBiEmQlx0nGMGPSJixFY4gOK430JKkggZN3OCHxlCJgDlQMP0CL9IWhWFhM06TYKzPiBOuQ9SwoohxMkyZQK7b8dXQHSaInaM7gUpSWLYziEg0jyCFAhtfP8lM9KLAznwDF4kzMilLOpTE4oEdBQJs7S7N3DN%2BKzJyS3IkS3KKrzRLytl6orfF2KNKT/No%2BTGOYlS1MizE6p8/LQLahAEmgsNqMS/dH0M4yXlmz9YxnBN50xNLGFYUUQt68L1MxMaJqokAQE2/yH1O5yDRfN9hMagr3K0mTytKxCQWQoiCM%2Bw5Y1YVFRW%2BsEvoRCqQTMQIIhrLwsAytwdW2dIbwSn7GQsqlAdByqyOPGruym2SgvRqz3sI36hC8dISitAAlT4vFoGMgZSoyKaprJafpxmMvMykScxMxQMFu4uFAjQXsc4HfrphQGaZrGrhZu4Zblnngp65T9oGtwNFA0W7mFsxCSukzSdR4LPnlvlxzw5AAH0mDrBICAgSZ0FOhRtod283DZ6n0BVxnQMD4rsBWGkODWWhOH8Xg/A4LRSFQTg3Gsaw7gUDYtg/CGeFIAhNEjtYuQCSRcQ0AAOMwzBSFIuH8SuK64ZNk2kaOOEkXgWAkDRdfjxPk44XgFBAXWC4TyPSDgWAYEQEANgIdJoXISg0BROgEiibbOFUCukgAWiSSQ7mAZBkBFsuzF4K1CBIPB3dF/hBBEMR2CkGRBEUFR1An0hdFFsUxAmDpE4DwKOMc46FyTpwdi0Il4xlQFQO4u8D5HxPmfC%2BuIzB3AgB4de9BuLmECFwFYvBx5aDWBAJAa9FIEJXhAGhG9EjACkILGgjMJqUFiFA2IEQ2j%2BlAbwXhzBiD%2BnYrEbQmAHCCNIGvSCBB2IMFoAI3%2BWBYheGAFiWgtAR7cF4FgFghhgDiFUZJKRjhLS6MTpgVQUjoQ7DzhEJE7dE60DwLEIBoiPBYCgROPA3c9GkC4rEDmTxDFGDcUYQuawqAGGAAoHsHwxTsSDDIp%2BwhmJv2kOkr%2BagoH/30EYlAadLD6HcSPSAaxUBI1yLo/ebtPymEsNYMwA8uJriwBUiAaw7DmNyC4NkMw/CizCBEEY1QxiixKDkAQQy9DTKaIsUYiRRa9LVAIAY0xPBdD0GspomyhhjKWJM2wUwOjbMKKss5SyJkrJ6VnbYEhwEcFjqQfuvBB7IL3ofY%2Bp9z5SCwTg3At9CG51IfnaJaxxpMCwIkbppAS6SECLiFIgRW4aEkGYSQSRe7%2BDqO3TupBu7ENxEkLgSQK4pCbkkfwkh66oqSG8qBg9h6jwhRPShs8qHzzgcvCgDDUD4M3tvDgbQWDmmTPvJg1YDDPi4CkXEXBy7X3wEQDpeh0kv3EO/HJSg8m/10ILQBwDBHPNee86BHBYGL2hHcRBXzUHHxrEYkWCqlUaBwXg2hCQkwQzMOC8hk9uWMLofykNYxnVGHlVwXW7CkRSS4TwvhoiZHCP4eIyR0jAlyOvIo5RUC1EaK0TomRBijEmMTvge0FjPhQJsXYpEMinENCgW4jx/DvE7ETn4gJedgmhOROWwy0S%2BBxISUklJjA0myC1Vkj%2B8g9U/0ToawpUSmlWFKW2rpVSakCDqQ0sy66WltISB02tlTeh9OcBAVwcyRlshucsKZWQZl5AucMjIL7FlHOWbshoV7mhnLvZe9ZgGFg/tubsoD76oPgcqL%2Bkh6xNiPMQ%2B3c1zLOAOp%2BTKl18rFXlyBaqkgvriEBshaQaFsLKDPMJcShVGLkz%2BBSC3QImLsV0qZb/Fltg2WBs5fAblC94H0PDcQLebBOBirQSwBQ5pz7mjw96SYKqQX3w1TOzJEhsmyFyUunQIBgjGpAXos1kCuMwN5QgpBqhpOyfk4pg0kxPWCu9aCwIgQyMcqntQlzTCRO%2BYISAOTVM7YKZSHbJTBA7Y2eyXQeNI8IDcN/mmlNgSUtiIkeYmRObBB5pUZWzA6jNFiBLYEstESu36LMWqSxdbbEOkbYE5tLjeBts8f6Ttvi1y9t4P2pQYSh1RK87Et847MDJNSYEzVmmdU6cXfkgzq7jAlJsFu%2BAO6mi6N2G7YpzTLCtI%2Be0%2B%2B574V7P6TewZMH73oEfSchZuRgP3fKBBp9IH9nQYKB%2Bs7GzrkvZOfMLZn3YPtFu3cpD2cnn6AgZxgemGYt3Bk3Ju4YXcSRcIyCkjJCyHkco2MeFBKu4gBrridz/gG50t7u55MFKYcfM4Kyse5HEX%2BBRc3ZMvcK6SDrlwKuZhGXt0CGZ2HQ92UUOeVfWnlrsccrWFxbIzhJBAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_turn_over/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/turn_over.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_turn_over.test.hpp)
