<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateReverse`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-reverse">To Index</a></p>

## Description

`Pagelivore::CognateReverse` accepts an operation and returns a function.
When invoked, the function instantiates the operation with its argument list but in reversed order.

<pre><code>   Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>n</sub>, Arg<sub>n-1</sub>, ..., Arg<sub>0</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateReverse
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateReverse
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will turn over `0, 1, 2, 2` and instantiate `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2, 1, 0>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateReverse<Operation>::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateReverse` with the help of `TypicalTurnOver`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Shuttle`.
When the entire list is turned over, we transfer the variables from the final `Shuttle` to the operation.

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

We will use `TypicalTurnOver` to turn over the variable list.

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

We will use `Send` to transfer variables from the final `Shuttle`.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateReverse
{
    template<auto...Variables>
    using Page = Send<typename TypicalTurnOver<Variables...>::type>
    ::template Rail<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxuxzuQgQXgIBHo3yOwIImBYaQMSJMgTcTGhqAAdPiMdhQZNiF4HBCoTD6BirNdQf99ndsKokQx0BYmMgANbww7A3a7O4AdUwdwA7nRaHcvEo7gQEHgvlQvAwHDk5ag7mhVUxWbrRQQxZq0oMFLjQUiUWjMBi3AQAJ4vZhsfHmwJE64kskEJks1wc7l3EwAdiswYeNNBFuRqP1ttBd0Tcpj1tt2KIrsJWoMCi%2BQkwAEcvG9MKQE0n03j8QA1Np4JixegKKPu4kEUnk5ms9mcrm2/NFku22vEeuNz6Z1utumh8uJy2x9GYyuuq7AYiYZGMAjN6dXJPSrJGO7KJjAUUYh4QwvF1U2zEjsdN12kO5rjdbwRmglT2kg8ORnSfzgvmbK8uc0ZWnGmIOk6rCYJOHpXF65KgegQazgBgR/pBi73naKbQViOKIdmTC5teg53q%2BK41nWDZNoSbYdj6aH9jeQ4PvR47fm6RJ7iGf4HguqYwYRS7ERmP7YGRFEAPIvMQuo5Ex1wHihPpPK0dBzhhQkHkmMoRMAcqOhegRXgpCTKQIw7cc%2B0mAfuSYhhG2FRmpSYiUR3kSbRfGybx76bmwX6qc5iZGceABKTB0EGFmPJg2m0LawWfjuiEgCAsH3jhWE4cB9wjvasR4AAbiQ7AgAAKo6eCiLQNWbAwcnlQk4HAs6nwmtsdwlWVlUbnpHlXL5%2BH%2BeFGl3HVaQNWIzXEK17XECNBWjeNaY4ncABieDEJMU3tt6M31Y1i3LQktp7QdBDhYJulRSZuUJVekLQrC%2BE3Ydv5RutQFjeJE3bd9BA0dt%2BbaugR0sadc3nS1bVXZioOvpDAjQwJs6eZFR7PWZr0Uh91KYujbKvqDTHuTObmFYDUF%2BSD%2B2TODRDXlDrNVricnygku5IdNs3zU1iMrddzNg%2BzGOvjzCB84hf36bjxmmS8umXr63YBn2MFmd1cPCxdSPELasvy9J2W5eFB6W0DJ5nvhZPoBTEtU/ltOja5o0MoCvsQUVhx3AAklaGU2QwnX0n70f%2ByC1ybWJDPA1JAXIDmXxWUpTQwydHjAMwSLRZgK1KIrukJ5JXOPgxnzW4ZeP2%2BehNsTjCVuLpwl6/B/VtKVFVVdlQsI0txt2aONe8XXBl3JbZnq3uNs5XbsU6Zimfh27f0ewDPvR/y4LMqwqKij8UcxwintmIEERp14WBt9q2xpDu90B4y69NJH8dA1tKc5%2BSH8VLUzjmCe4QgvBpGKJgdARcFBeFoD6U%2B1wnoQggVAmBnx4E%2Bg1oA2ymIzCvgIXcLgr4NCbx3uCAAsslJgypVSfyQfTPCv8uZXGIMAfmoIUHUNaHQtUAhCZ5wLpgIuJd8K4IYISbKp5zxpXYZPX6FD7iwKwV/K4KCVEIMJjw2hKp%2BGSMxBoV8JC7hELMOQkBDIZqfEQRfT0rRHDIAAPrkSUO0CAkx0DZQUPBFxu43DgMgZkaBmjJahMJCsGkHA1i0E4P4XgfgOBaFIKgTg7dLDWDuAoDYWwLxXx4KQAgmholrC5AESQuINAAA4zBmAAJx1K4P4apVSuDBmDNIWJHBJC8BYEkIxiTkmpI4LwBQIAjFFKSdE0gcBYAwEQCADYBA0jQnIJQNAKI6AJCiPBTgqgqnJAALTJEkHcYAyBkDEIqWYXg0DCAkDwF4kh/BBAiDEOwKQMhBCKBUOoKZpBdAkLFEpNInAeAxLiQk4pKTOByWhCsn0qAqB3H2Uck5ZyLlXNxGYO4EAPCbPoKtcwgQuArF4JMrQawIBIA2XNQlayIC0q2YkYAUgCE0AQXzSgsRoVlWYMQe0YLeB8t7nJWI2hMAOCFaQDZoUCByQYLQQV/ysCxC8MALEtBaBjO4LwLALBDDAHECq/akrHDtR1ckzAqhJXQh2AUiISIunJNoHgWISkBUeCwNC9seA%2Bm6tICtWIwSngGqMK6owxS1hUAMBw6sHwxRWUSQUl5whGofOkKmn5ahoWAv0IalA1hrD6DdWMyAaxUDPxyDqw5njLymAyZYMwQyVqjiwGWiAaw7BmpyC4NkMw/AkLCBEEYVQxgkOKNkAQA69CTqaIsUYNReg9oEAMaYnguh6G7fotdQwR1LHHbYKYHQN0FBIfMdoC6x01C7Tk7YEgIUcHiaQQZvBhkooOcc055zLlSGxbi3A9yiX5LJYUqNaw5ZMCwIkTtpAymSECLiOpgQOkaEkGYSQyQNAaH8MkOp%2BhOA9NIH0kluJkhcGSFUuprTkj%2BEkE05DqRX0wpGbYcZYGplUvmdSxZ8LVkUEZagAl2zdkcDaCwcqwZDlMDIseLgdTcRcEqbc/ARA216FTW88Qnys1KBzf83QBDgVMFBbqx9z7mPDLhcs6EdwkUfrRactOhriEKaUxoXF%2BK6UdWJWYUDFLpk8aZfSgTwWxjOaMPJ2ofA6BIgOty3lERe7SpFQKsVEqpUBtlduBVSroWqvVZq7V0r9WGuNck/AG41QWuhda21SJpWOoaNC117re5ep2Mk31/qClBpDciMrxko18FjQoeNmBE1OmlZp9NEhM2yGzX85Jhn82RobVYSwJbYgdorVWgQNa60WXW9YZtb7W2PM%2BPALtDQV1%2BAgK4GdQ62RXuWBOzIU7cinsHekd78792Lq3Tdndx7HvLuBwsf716t0g6%2B9DiHFQAekvWJse9SOukWehe%2B1FX7ZMmXk4pypAHVMkCDCB8l4HSCQeg5QR9RGSMKbQ8GfwdT2mBHQ5h%2BjL7MecFGexgLXH4A8aWQihlYXiA7LYJwcT6KWAKHKpc8q%2BPrSTBU0Bx5GnZBaYzV8%2BQemls6BAMEYzpnwUEafVC/5Vm%2BOIuRaoGXcuFdK/1JMTzQnvPAcCIEfzw2gtu%2BZaLv3hKQDy8gU4xXdSnHK4IE4u3mbYtcogDy/5qXlUFJT%2Bls10rsuCFy8qirmA1UarEMVgNpXw2db1aa6rl3/l1eQHaxrghmv/Nax6%2B0HWfWjh67wPrShQ2DcjZxkbZ4xsJqTdNzXs2dMLb17mw3q3jBFs261nbKS9sMB1bsTxhbG0WFOyk877artg6aH29wsOnvoBe4eudORQe37KJD17J/%2Bgw/yN97dTRd3X6XRek97%2B4dL0n9x1b0UcPlzMLchlOAUV7d5c7hw9cQo8icgNScSVvdOMINMAoMxhYMuk6cQB6lcRPd/Bml6NsNPdgxKMudLcec2MJkKd4N/AkM2lgxsMqlJBGkuAakzBUgulAhIC31aD%2BdH0blqCoDWNhDA0%2BZe1JAgA)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_reverse/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_reverse.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_reverse.test.hpp)
