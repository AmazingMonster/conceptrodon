<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateReverse`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-1">To Index</a></p>

## Description

`Mouldivore::CognateReverse` accepts an operation and returns a function.
When invoked, the function instantiates the operation with its argument list but in reversed order.

<pre><code>   Operation
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Operation&lt;E<sub>n</sub>, E<sub>n-1</sub>, ..., E<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateReverse ::   template<typename...> class...
                 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateReverse
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will turn over `int, int*, int**, int**` and instantiate `Operation` with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int**, int**, int*, int>;

template<typename...Args>
using Metafunction = CognateReverse<Operation>::Mold<Args...>;

using Result = Metafunction<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateReverse` with the help of `TypicalTurnOver`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Capsule`.
When the entire list is turned over, we transfer the elements from the final `Capsule` to the operation.

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

We will use `TypicalTurnOver` to turn over the element list.

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

We will use `Send` to transfer elements from the final `Capsule`.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateReverse
{
    template<typename...Elements>
    using Mold = Send<typename TypicalTurnOver<Elements...>::type>
    ::template Road<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHOaBEcjeWADUJoFuXo60hACeZ9gmGgCCewdHmKfnyJPoWFT3jxezwA9AAqcGg45uJjpBReejHCGg4GAgiYFjpAxos5uAg3dKMViYAB0pIBz0mxC8DihMLh9DOVmegMBYIhx2wqjRDHQFiYyAA1oiISiQcDjgB1D4AdzotGOXiUxwICDwCmOVC8DAcuWVqGOaG1TG5xo%2BBGl%2BvSgwUxNR6MxppxeIJzDY5KelOpBA5XNcfMFpxSVhSABFGSznmiMVjME77TGnfjCWxSbbAtgDQYFOqPIImBEEqRlUnXSTSdh6GxBAp3Z6aZzubz%2BQKcbnWgXiDiK%2BjGAQbWT0%2B6TEHAccx8r447zs7k2XidgeRFgDXB89xwrskZjgBZTzoT4hqGyfORTvnbtVvuposL/BGftph6BJkvUPh5kgpHHISuYXg0VPFGDrYtOJZEqmtYEFSNI/jygbBmGz4RoBk4gbiqGxqBLrgQOGaHEw2ZHnmHZFjOpaphevYrg8FJQV636uK2x4dl2lZURBg6rq%2BL7rkBCbThhibYSmuGZgR6oAPIEsQxq5O6651t6IaYO2tCjuOw48eu46KkuxYEgexxSQkskCKxPbVhxT5aWOw6IS%2B6ljnxU7odGLlkThj5idmqZPMAxCYBZfbyTpm7AMcABKqBMPuZyHspqk4n5AVBQ%2B9wgCAM7vq%2B9nIWy4LHAAKvieCiLQhWbAwEkAG4JH%2ByJ2m5aEeSJj6AopRUlWVFXEFVtXEPBdnZY1wGYbiYFsMcABieDEJMkHQd6xXpKVYg9X1CQ4jNc0EEOI5rqFekzoZ0KwvCY3bfNnEOW%2BSEfihTVjS1HyXQQpETR8P6GugC30ctq3lZVNWbecr1Fl9Ag/VxmmORuR1JiddLnTiEM8kWr0AndOXDZGglYbO02zZM73CZ9mDfSTs6phJKoJNR7V0TS/3dUD/VbUTb0MRTRm03NVksvtTzrrpW5ZQdtmBIeDZ%2Bs2QkE8za2syDbg0wgdNWRlWVceumsYTue4o%2BTkPoxzmM3bl935ZCHjAMwaIRZg/VKkiAHOc1ePjaTVneZJ0mmQwv00jbduYA7Tuxsygu8R7z0UWx1YhWOIvhbutCxZLDE8nLpadStLO9cDZ5uJRlm4ZrSaJ8cuuPZF0VQyrftNGbAsW0CTxW0inf/qyX6FZgkzqi7PddyPDX3a82rvJ8FxXLcQ64492eeYH3rGTJTdY4Cyffl46QlJg6AO/S3pxUZjdyecEQEOCRZXzfxx37fgjN/dbtPR9vnEMu7rb9uKlMJqbUTQTqoFtqaMOdMxpr39ulEAqd65PC/mla6yFt5H3hCfDOf9WiAJ1GZS%2Bggn7XyIffO%2BoIX5t3mI4ZAAB9cSCQCAQB%2BBlBQRI6ErjcEIXe%2B9D79wwUWdBtBdrphWIyDgaxaCcH8LwPwHAtCkFQJwNw1hrDHAUBsLYHw9g8FIAQTQ4i1gCgCGYYkKQzCSCSEkfwGgACc/gzAaAAGxJGCJIjgkheAsAkBoDQpBZHyMURwXgCgQC%2BL0XI8RpA4CwBgIgEAGwCDpEuOQSgaAMR0ASFEIknBVBJEcQAWkcZIY4wBkDIGOFIYkZheAH0ICQPA6A9D8EECIMQ7ApAyEEIoFQ6gImkF0FwUg0oZLpE4DwCRUiZH6IUZwCSlwknelQFQY4uSClFJKWUipkgqnHAgB4dJ9ABraJWLwcJWg1gQCQGklahyUkQGuRkxIwApBmD4HQNEc1KCxGmbECIbQbhjN4L85gxAbgSViNocm4SdFpMvBJBgtAAV9KwLELwwBoS0FoCE7gvAsAsEMMAcQyLZpQrwLVbF8jMCqHJpcHYOir4NGmdcWIMlQUeCwNMqCeAvE4tIP1WIWRMDKXxUYa4Rh9FrCoAYZcAA1PAmBpTGVkTo5pwgyrtOkKq7pahpkDP0ASlAKjLD6DwLEEJkA1ioHSE0bF%2BSfhxVMJYawDjeCoH6sQBp/d4BrDsKS5wEBXAzD8IMsIBYlhjEGSUHIAgg16CjU0RYoxEiDN9Xg5oUwOieC6HoVNTQBjtETdUCNtgM2xpTRmwtywuA%2Bo0dsCQEyODSL8dMwJKy8mFOKaU8plSzC7NwHUo5ZhAjVtORKtYasYpjAgIYkAkhAjEhsYEFIkgNCSHMY4nx/hHE2P0JwDxpAvHDuJI4rgzibFJFPf4SQXB/CLscc2vpgTgmhN0RKqJsTLnxPmckig9zUAHMydkjgbQWDVRSPkpgYktxcBscSLgxJKX4CIB6xpgzVWtPEB0rVSgdV9N0K84ZMJAUNqbf411szv2LOWSBsDEGoPhRg3BhDuz9k3LqnsMwJzX0RIuVc/9bGyC/oeYckANHwP4SMDBrgviaBCLpl8n5fzQWAtIMC/54LIUOBU7C3s8LEXTJRWijFWKVN4oJUS%2BR%2BAAo6nJdMqlNK0QqYZW4%2BRzLWU3HZTseRXKeU6P5YK4V5mlxvqlUwWV8rFUuhU%2Bh9VEhNWyG1b0%2BR%2BH9XisdVYY1zLzXToUda3Itr7WS3S86gJ7rPXZZ9Q0P1fgA08jLSEHklbi3xtyPVlr5Qw1JpzVVtN%2BbM0FGDb0arfWmvJpLYMer8wC2daLcmmtmw63Vt3Y2qZj7ODHDE3RiTDHYPwY0H2pDJBThDpHdx8547MCTsSDltx%2B7D2wdXSkW9KQUiBDXZIIpgyyMzKCbYF9ZzInRLiQkhZdzhOAbYJwED6yWAKGquU6qjGYyTBqYdlDTTZAYY1Z0%2BQOGks6BAMEQjoycUkdWwEijiTLjHCWRt4gLAYdw4R0j00kwWP8cecdwIgQuMA94ygDntyhOC7GPDveNDEc2JocjggdD6dFLeXJz5EBvl9LU8p3l6uwUQqhdp/9cKEVIss5gVF6KxAmd5WZ0VXncUkps16vp9nkC0qc4IRlfS3P/M85yj1vneD%2BaUIF0VwWeN8GlQoOVCqlXRcx7FrDCW8e6sJ6l4wRqbBZe9blm1nBgTMOK5YF1CiytYAq0NtNLg6tZsKCGxrM2q0ZCyNGvIVfBvtYYKN7rfQBB9cmz1vNFa6/Fqm/17N5aFiD7m%2BsBb7SycPopxwOnDPimw/h8cSXxIZcHYHVz07fOLtXcoA2u7IAzCwe5/4ax16fHc5SM4uf5HfshLCWO0gRjJApCqU9rgUgbGPcXVwNINxQIcnB/UdHjBtape/H7MA87PlOmXIWdIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_reverse.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_reverse.test.hpp)
