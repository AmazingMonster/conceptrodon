<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalReiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-reiterate">To Index</a></p>

## Description

`Typelivore::TypicalReiterate` accepts a list of elements and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Capsule`.

<pre><code>   Es...
-> N
-> Capsule&lt;Es...<sub>1</sub>, Es...<sub>2</sub>, ..., Es...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalReiterate
 :: typename...
 -> auto...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalReiterate
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };

    template<auto>
    using Page_t = RESULT;
};
```

## Examples

We will repeat `int, int*` four times:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<
    int, int*,
    int, int*,
    int, int*,
    int, int*
>;

/**** Result ****/
using Result = TypicalReiterate<int, int*>
::Page<4>
::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalReiterate` using recursion over the times of iterations.

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
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};
```

Here is a simplified version of the implementation:

```C++
template<typename...>
struct Capsule;

template<typename...Elements>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAc/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOt2wqgIrgsTGQAGsvocgVCWGkDFCTIE3AQAJ7PZhsAB0xMx2BBE2IXgc4Mh0NhCJMAHYrIz7pirFcQSi0UwMViQbdBbduejMJjsXjGKxMMTCaTbsgDApPh5BEwIglSAKhbj8dLZdh6GxBAoQaTyQRKdSIVCGOgYfDxaqWhriOLDZhjQQFLLzYEyZzmdrBSLeWKsbqpUTiZdgMRMJ7GN7zVchbcvFkjLcALKedC3TH3W7O9WRN1Yj1en3E0i3WPxxMm33%2B9lm1mtzm/MFuJhpBReeiIg7Iz08vkSvXRuUtq4UqkEYu9/v0DvArsAjffEF/Pa3ACSqKNSd5OSHZ23m8v587l1D48jBJlxMrSdNM8uc%2BpABU8XhRLQACVMEIBIwzbDlLjTO9wx7LwiGbANIKFT8F2UYhUCIZQmGATACyDdtAgg7cdluGElEXJQQGDYVR1FcUmDg1B9xTJDBXjABHLw8HjT4ID3AtAjZQTbg0ZZqJQ240Iw1AsJw8U9xYtMmQgtM0wzCJgGFSUBKLHs%2BwHGC/RUoUmSEojUx1WiwKxBiiGY980w4rieNuPidMLW4uDEizBQkqTMOwmCFIckygx81T1KzSMdMXfSVwrI8mxJFtCOo0zV2I24gOQDYsgAN1wntKOo6D6MY%2BzEMczBOO4j5XLMAS3A8vdvNY24/PQgK5KxYLKtC4zVPTTNNOijybTpR0I0lR9JM6mTAvk24AFpbjMUkQBASNFMG24NugnM83dRLvVlWsXyS6cyVS8L0uutc2tKmzGNlesEyrbbBUizTZNwjz/Pm7q3FexsTuSq6iII8zQSvJELzuCFWDRXCt3XGHr3u8xAgiRUvCwRq0AYLY0mTd84YOWLl2R2GrkeicoyfS6LStBc9MpjLUd3IQvDSYpMHQIDlwXFHLi%2B24uZ5zI%2BYFgcFw81mDPFaiIgIWtlb2LVwuV1XBHVpXBG1ghdc1/XbjVs0Uqhncso%2BGWzyBUXpdoWXhJ/NI/zEICQOIay3C102dZYjafvFSRA82yV2eh8mvw%2BIXqY/FpHGQAB9JhlQSAgIAmdANoUaVU7fNxHZVsXud5/mbad0kxMIjhVloTh/F4PwOC0UhUE4JrLGsdr1k2X6zECHhSAITQ69WOEAkkQkNCSMwzAATgXrh/FnpIuEZRlpAbjhJF4FgJA0DRSBbtuO44XgFBAY/R9buvSDgWAYEQEB1gINI4PISg0FROgEiiaUnBVBJAAGxLRAZIW4wBkDIE8tPMwvA%2BaEBIHgHOXAZCCBEGIdgUgMHyCUGoMepBdDoIAO7ezSJwHg9dG7NyIefAA8nBD%2BC5UBUFuMAsBECoEwLgYSBqEAPC/3oMQAsg8vK8FvloVYEAkA/zdiIr%2BEB5F/0SMAKQZg%2BB0ChMQK%2BEBYhENiBEVoOIqG8CMcwYgOIGGxG0JgBwZjSA/y9AwhgtBTF31IFgWIXhgA9loLQK%2B3BeBYBYIYYA4hPH4HjA4PABUglt0wKoexcFtjD2VvUIhtA8CxG9lYjwWAiGWjwAfYJpACrEFiJLR4YSjDZKMGPVYVADDAAUAANXeKQhh%2BJHH8Ewf%2BHB0g%2Bn4JUOoTxJD9DhJQNYaw%2BgclX0gKsVAxMchBKWtnQsphu6WDMGfCpxBUEfHgKsOw9jGguDtNMPw6CwgakWKMdBxRsgCCuXoJ5jQFgjESOg05sSBD9CmJ4ToehfmNABYMO5XyQWTHaECgoPyYWfKqA8k5fctgSBoRwJuJ96GcA4aA8BkDoGwKkPw1yuBkGiMxhIkejTVgIEwEwLAiQIATxAJIQIhIF6BC3hoSQZhJAgKPv4EBC99CcD3qQA%2BQ9CQgK4CApIC914gP8JIFe3KQE4s8efS%2B19aV3xkc/WRr9mGfwoMo1Awj/6AI4K0FgeVGRLSYAqAwWYuAL0JFwGeiD8BEAOWgvBWDxC4OGYoUZRDdCaPIb2MxmLsWn14Iw01rD2GcMJS68JnkPVeo0K5IRCiEhiMCGYZYkjGkPzkZagtZBzUqJESgV16jl7HxoE7BIeiDGeIsSYxx3arE2LsQ4spzikyuPcUQ7xvj/GBMcaE8JkS27RLOXEo5nikkpKhI4jJO827ZNySYgp2w27FNKcPCpVSlA1PnRpctzTsLtM6d0xgvTZBBsGXgsNhDxkgE0Y26Z2ybB7oWay9uKyBBrI2YJLZVgdl7ISP6o5iyejLucBAVwrybl2iRUsR5mRnm5Dhdc9IeGPmQuRd85Dfymgwow5RsFiKyM4dsDRwj0L5iMZRWsDY6KvLiqxXQ7VeK03cMVJm91nqZ7kt9SQItNKpHj1IAyplowQM70ldKj1fLGT%2BAXpvQI/LBVqq1WfTguqb7lsfi/N%2BLClF1utWwTgdruEsAUHlWBeVxOigmD6ylqC9DDLfRIIZshP1jLbroYI0bKHBLjQJkzHAmHvzgrcNhHDnOufc55sMEw81VtUUWwIpb9XSIrSgPLija3ldGG5nmycPML2Tl5ggydVAQK0W23RlBO1tz7R44evWB1nMcSOwQY6PGLswD4vxYgZ1lLnXUo9ITaqxPiUQ9dOVN1lO3VknJeScSHqKQc09vBz3VM9NehpBq%2BAtIfZgLpPSykBYGUFj9BCws6BAMEP90HZlAeOaBxoQSdjZ3/TBiwuzE37MOcBk59QUN%2BDQ5c1jmH0DYYecRkoORaPvJyGjijoK%2BgsfyERgn/yGMVChQigYtG5htDxxirj/cGc73jbijgaXIEubc7cerhImtScpbJor8nlj0sZcyygmL1M/o9YEQI/hV5qqPnLxkCrjOJtM7YPVIu2WSH8FyjejIj5JEkMvLgc8zCap3oEOLGuL7FYUzvBB6v26a51%2BU9tOR2VAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/reiterate.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/typical_reiterate.test.hpp)
