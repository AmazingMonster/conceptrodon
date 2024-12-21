<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRepeat`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-repeat">To Index</a></p>

## Description

`Pagelivore::CognateRepeat` accepts an operation.
Its first layer accepts the times of repetitions and returns a function.
When invoked, the function repeats its argument list the given number of times and uses the result to instantiate the operation.

<pre><code>   Oper
-> N
-> Args...
-> Oper&lt;Args...<sub>1</sub>, Args...<sub>2</sub>, ..., Args...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRepeat ::   template<auto...> class...
                -> auto...
                -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRepeat
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four iterations of `0, 1`:

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

using Result = CognateRepeat<Operation>
::Page<4>
::Page<0, 1>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateRepeat` with the help of `TypicalReiterate`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Shuttle`.
When the iteration completes, we transfer the variables from the final `Shuttle` to the operation.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

We will use `TypicalReiterate` to reiterate the variables.

```C++
template<auto...>
struct Shuttle;

template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
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

Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename TypicalReiterate<Variables...>
            ::template ProtoPage<Amount>::type
        >
        ::template Rail<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxCAAnADspAAOqAqETgwe3r4BaRlZAqHhUSyx8cm2mPaOAkIETMQEuT5%2BXIF2mA7Zjc0EpZExcYkpCk0tbfmdtpODYcMVo8kAlLaoXsTI7BzmAMxhyN5YANQm%2B25ejrSEAJ4X2CYaAIIHRyeY55fIE%2BhYVEezzerwA9AAqSHg05CBDXAj0U5Q8Gg4EETAsVIGdEXNxMa6oAB0xKBrwmxC8DhhcIICMwFysr2BEKhp2wqnRDHQFiYyAA1kioaiwaDTgB1L4AdzotFOXiUpwICDwClOVC8DF6AkVqFOaE1TE5hq%2BBElutSAwUhLRGKxxtxBDuqUYrEwxOt%2ByeZIIFKp7M53N5ApMSSsSQAIgzgTbMdj6Zdgack4rbXHcfiiO7HnqDApVUJMABHLyMHakRPJjNE4kANWaeCY0XoCmjnuB5MpBDZHNcPP5uILxdL8bcdeIDabmCtJLbbaZoYrSfRsftlyr7pewGImAxjAILbnL2TcsyRlOyiYwC%2BF3DMKLJc1I7HE%2Bb7tIp03293gmnHqe%2B0ZN4IyjJkwWRO8uUFSFhReZc7RxS5HWdZg2CzQ8OypAtIJDMNIwA6NXjgtNENTVc8QJNDsBzJg8zvIdH3fdda3rRtm1JF4MK7LD0AHe9h1xZ9WKnSj2JwxcUxXBC3CIsimL/ajaIAeWdYhDWydjj0405w0wJo6HEsTXmPY95TCYBFSda99lvZS4jUgQBJYydfyBfCjOTEM8MA8SZKk3yRzk7Njho39Px3Ngfw05NTLPAAlJg6G%2BW8dL02hcTC7990okAQCQ%2BNvOAtyQReFlIVOAAVJ08FEWhYswQg7PRKCURjeCAoo5jxyEg8vQ4n1OwqqqarqhrVJxedAOPfz0w6v9xK05RiFQIgLyvc4F0K7yRVOHkFTxJQQB80ipKrU4AEkoqTbdizwbdVQgM6kpvU4NFWeb%2BqpRbltQVaRwuw9j0Mo9jKTGLzLypLqXhehcVcyaPM2gjgaXY72qIc7LtOa6vFuqdTgep7rNOLg3vcpMFqWlbLz%2BzGgZB0HT3ByzIdhaGnyc18Z3/eGk08kDitBUU6uQLZMgANy%2Bfb2COyS0d1f7euPbHcfusxvjcZ6ztJ5HTgp77ftxBWDIXMnjLBiznUh/1eyDB1LJQr4vqpq9DdOABaU4zEeHK8sx48fdR89qccrrnLfU5BLDrn%2BcBxHQJ16a11mjKIv3THzd%2ByGnZ%2B4PLhTvcXNnAqvKR0roQ8YBmHROrnUNZqYMT6TUZmzMuYU1VbLG9T0I%2BrsK6rzAa8wQ1oxNhPm8uTIAC9MAAfS7F4WE2QRMb1536VNun6cbuTI7YgH6Yz6mWdccTAYTU36Ytl02EG1JqrEEb0TG9nQ85ubL/pgPZfPSmc5dvOS8NQEG9rlSyZ8PIHxBt/Nqpx4r6UuJ3eyDA4bGxLvHKaE83DTzngQDcW5woF3TozIOa1nrZwNnnAhmVC7c1HuggWyImHMJgmXCqU59z12ZMwnh0EkbvE1J8dW1w6D3FEoRLBgUe6%2Bi7Eg%2BoKCirAnNkILwqR0hKHQHVBQXhaBdmenI7uGtTYaHfFwcsxjTHmJ1iY4mVjjw2K4K2Oh8dzZaJ0Xoom/djRDxHoglSyD2I5UoW4SQgSQDBIcag%2BOEw1LIFniFOIBAIB/BygoV08SDxuDcbo98Ki1EZEwJoqc7jHhvQAhwdYtBOAAFZeB%2BA4FoUgqBOAa0sNYXWmxtjXjMPsHgpACCaAqesPkIBqlmEJEkMwkgAAc0zqkaASGMjQ/hpn7H0JwSQvAWASA0CY%2BpjTmkcF4AoEAJiBkNIqaQOAsAYCIBAJsAgqRrjkEoGgTEdA4gRFdJwVQ0z/Bu38JIU4wBkDIGJpIQkZheCFMICQPA6A9D8EECIMQ7ApAyEEIoFQ6gLmkF0GYyUqlUicB4JUmpdTBlNM4Ipa4TyuyoCoKcX5/zAXAtBeCyF%2BMPDvPoMQc4PSSa8HOVodYEAkBvPvryl5EAJUfPiMAKQZg%2BB0GficiA0RKXRDCM0O4JLeBauYMQO4ilojaB6OcvpbzU6KQYLQXVuKsDRC8MAPEtBaAnO4LwLALBDDAHEA63GvQJYesaZgVQPRri7D6WEdEVTcW3GiKpI1HgsCUp9HgbZnrSAS2INEApOkfVGFuEYQZ6wqAGGAAoGseBMCSlsvUvpSLhA1TRdIJtWK1CUvxfoX1KBrDWH0HgaIJzIDrFQKkeRHq3Z/BvKYNplgzAHJzeOLAI6IDrG6FqPwEBXDTA6EELkQxyiVD0Oo4oORPDtFPUUeRR6RjxDMZu%2BR/QpiXpmDUOofR5h3uWA%2BuYAw916BiS0H9J6SYbC2DsCQZKOC1NIPs3ghymV/IBUCkFYKpCcogLgWFfKDiCv6aW9YCBh5YHiOu0gIzJD7EJAkfYSRJAaEkFM/wuzqn%2BASOsjgmzSDbN6YSfwnRpkJGmZ0apkguDVLo4EBDVKjm2FOYRi5orblivubS55FAZWoB5Z875HBmgsDFkkN2TBqJni4AkQkXBCShvwEQFdiLZAovEOi9tShO24t0EqwlTBiWepg3B2ThyaWPOuKcBlpxDPGdM%2BZ8ylnrO2a5TpyVcR%2BX7DMKsIVparnipS3K6VsreUgGiyZ4KRhLNcBMTQXRcQ1UatxQanVerSBNaNSas1DgWtWr3Dau1lLHXOtde6lr3rfX%2BsafgbcQapyUrDRG9ELWY21EpQmpNdwU27EaemzNfSc15qUAW8bZkcvlsvFWmtdbkItabS51tGL5AeZxY07zPaS1zqsJYQdw74BjondkKdM7rIfesIuxDy74WzdHR%2B812QXBckA2YkIixj2jDMWe%2BRiPCiZFvSj%2B9QHaiw4aPMLHT6v0DFA2j/9r68j7uAwsMo%2BPwMKE6VB8DcaguUqQ6V2L5X4tWZsxofGOGHPpYI8KoZpASNMDI5QGDPG%2BNWaY0kKTSQkj7GY5IQFZjgucGOYpiXKn4BqYeXSwr%2BXeVfLYJwQzrKWAKDFmCsWCW4wTGhfZuFCKzG3ZbRINtsgO3PZ0CANZvn/Okq45z3FIWNP0sZbboF9vHenGd1Z13XYIDctS3hnp%2BwstKZFbllAFu4jm90/ER3ajZ6p9nun%2BJxAWCAuVbV4g9XNXaqNS1trxrTXmu6zp61tr7WTcwE6l1YgRtZrG0WrbXrA2OGDXN8NItFtZuW3Gxpa2dWbbTeOXbvB9v5oxMdktym%2BAVou7W%2BtN3nO%2B7cwHp7XaQ9veMP2r7Ca11/cnZwUEKSQcLqXTiBXShwozJ2cB3QRzfX3WR0Z1/WvRx2yCxwx2yEpz/TAIYBfVaCgIJ0/WJwpzxzgMfRJ2wKIPwNgLAw3VZzRUCwpWj04Ciwbztwdydxd2NAmGFw9xz16Xz0N2I1I1GAozjQVxADMCs32H2GqXmQk12XEKSBWXgy5z1wUzOSI0oxAEkCSEhRVy4CkASGVzoy4BSDjX2FoIOSUN4K4yhQULoPkwsJzUyGcEkCAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_repeat.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_repeat.test.hpp)
