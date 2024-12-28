<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Repack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-repack">To Index</a></p>

## Description

`Pagelivore::Repack` accepts an operation and returns a function.
When invoked by a list of packed sequences, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Oper
-> Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Pagelivore::Repack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   Oper
-> Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Repack
 :: template<auto...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct Repack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
/**** NewVessel ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<0, 1, 2, 3>;

/**** Result ****/
using Result = Repack<NewVessel>
::Mold
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pagelivore::Repack` is implemented similarly to `Sequnivore::TypicalPaste`. Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;

template<template<auto...> class Operation>
struct Repack
{

    template<typename...>
    struct Detail {};

// Base Case:

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    {
        using type = Operation<Variables...>;
    };

    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    {
        using type = Operation<Variables...>;
    };

// Recursive Case:

    template
    <
        template<auto...> class SequenceA,
        template<auto...> class SequenceB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
    {
        using type = Detail
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::type;
    };

    template
    <
        template<typename, auto...> class SequenceA,
        template<typename, auto...> class SequenceB,
        typename TA,
        typename TB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
    {
        using type = Detail
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::type;
    };

    template<typename...PackedSequences>
    using Mold = Detail<PackedSequences...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7kIEIiCPRvkdgQRMCw0gYWQSmIjUAA6fnk66TYheBzU2kEemYOFWa6g/6AxWHYEKu4ASTZ9DYgiYTUZyvlSqN5wpVxZmt10vh5vZlq5PP5vPRdyhTAUXwA8i9iLqcoKrsLRQQ7gAlZ5MZAAa0xAHZZSDrnck3cbRyrW4CCiXsw2I7/cm7oGxU9WnRYXGTDGHjLTbtdncLG7MHc3E2QKaC6m7dbWbbOfDuUQ84FsC6DO7qZgAI5eN6YUh3Qd8/kANTaeCYsXoCnzyaLwZLTDoBKE09nOPTa%2BIG63n2HGJHoILlfjBYLXiyRhTWebcIedy9BJfQEAkrxvbd7xrRNk0ratAnjJ9ky7fsM17NMCUzbNWHnRcHQFEcxzdL5TxnOcF0wxhsLuAAVH8FyXR0wM3bddyTfdHkwUtaBPM85wJWiXgXJjbwUSDH2gpMX0Qt87g/CJgG/F5YUCf9AJ9JpQPXZi73wh9XxgqsoITG56zDZBNiyAA3ZtWyUds5QklM0LtRyCWkt9kPTBjdMIicSPPbYrlIdzO2clDvKdAjXT83iLxsELkwi4T6ADBcEqTJKtNvCwFGCxzOx/HNMEdD0CAQBId1c8SrgLdjD2PeF/LnEF4WSzAA3vBcmrizTr20nLOoAsqKsg1yK3y5M5K/CjlP/eruImyT4XSt8aTpehevA9rRP5ISsvoAbdLymqZLfUryuIHanUW5TsBAEAKKM59DPgjskLC6UqrcFbPIwwrsPovDItHaLiNiwLjtOpyLRQiiisBocfNBydSLiyHTrhqjqKCn7/rYGj4puzK%2BtvVLYSJoG2py9GZMx3N%2BXOir3NYwsCBFYtOKPbjGvB9r%2BKCu42o6o6UYCzArHhaibEF/bxau9EF0Zy7RpOyTxtVt8poUma/w4riVrcm7aoIdB7oiFlgASAB9JRUe2Fbn2Wo3TuJe6WCYSNMBtvBgEidArYIAlXZALIAC8vcDkcaaht95kcZArdESYg5Nt2Pa9rJfcwf3I7cYOw4j8kRwgIWFBWR1o5jvdWnjxO3Vz4P3c972s5zlPTZDvBw4DovsBL2WcvLgVnaW7BK9OpX5Zu9F7se16xrghDHN%2B608eK/llAjT30G67Yd2q99PwUgBZTx0FmvWuYJTeo2z3edOB2efyM2CX8pY0mUNe5sFUVh2WbH4X8P4mgcjcKkURMAAHcVyfDsPqEBZoPrtzTs3TOfse7wnzl3QuI5HRXGIMAfeGJrjEDPHgUhXwIAF1QFQR0EB8GEJWLNXWkgVignYhA6BsCGhvzAfcIQXg0jFGzmGBQXhaDBkAdcLW1JBHCPQKI8RwZdacJge6Hh8INALi4AuMwC5AhFyXnww4oZPhKPgcCGRiiJEXzDGkLeBJVHcO5sQq491T60HQJiJ2Gtg7m0wJbYgNteYEnNguDQCtya%2BNTiACIWBVDBLtumHRdwzAK3cn4hg8TEliwJAY6qhjaxUmop8SRn8hQ1zwAnIiCQCBUJiQobCVs3QEmsQQLqcjMgiLMRI9EbD4IcDWLQTg/heB%2BA4FoUgqBODfUsNYQsGwti/nBDwUgBBNCDLWJGAIkheQaAABxmDMAATmOVwfwBz9lcBjDGaQwyOCSF4CwJIWjxmTOmRwXgCgQBaPWRMwZpA4CwBgIgEAGwCBpEROQSgaA2R0ASFEbCnBVD7OSAAWmSJIO4wBkDIDuFIXkZheDZ0ICQPApsdH8EECIMQ7ApAyEEIoFQ6h/mkF0DoyBPo0icB4EMkZYyNlTM4B6REkLgw0LuCi9FmLsW4vxbsswdwIAeDhfQYgsIVkrF4H8rQawIBIFhWkeFZAKAQENcakAwApB6JoBIiqlBYiCtiBENoKIeW8GdcwYgKIPSxG0JgBw7rSCwu1AQD0DBaButZVgWIXhgCtloLQb53BeBYHdkYcQ0byEBscNZZNkzMCqADYiHYqz/H3MmciWIPpvUeCwIKtmeBnkptINZYgsQulPHTcAZERgNlrCoAYQhK4PiQMAuM1ZVLhCiHEPSqdTK1CCvZfoQwxhrDWH0HgWI3zIBrFQGkJoya0XEj/KYOZlgzDvLbdeLAO6IBrDsDmnILgskzD8DosIEQRhVDGDo4o2QBBvr0P%2BpoixRg1F6E%2BgQAxpieC6HoR9Dh%2BhTCGF%2BpYv7bAoaAzo%2BY7QwM/pqA%2BxZ2wJB8o4KM0gbzeAfMlaijFWKcV4oJYqiAuBSXqqxFwLVaz%2B1rHKkwLAiR72kG2ZIQIvJjmBFuRoSQZhJDJA0BofwyRjn6E4I80gzzAhcF5MkLgyR9nHKuckfwkhzmSdSFRoVnzbA/J4/8vVIL9VgtFVC015q1WIrYJwNoLBLIxjRUwQiX4uDHN5Dpgt%2BAiA3r0FOmls7pDzqUIu1lug9GcqYNylNZGKNWY%2BSKiFiI7gSqlfR4LClQvhb2UqlVRq1UasCGYbjOqAXOY8wkaFZrUCqrGK6IwoXah8DoCyS6DqnUuu9UGz1rrfX%2BsDS2kNjAw0RqjZMmNcaE1JqDWm1dma1vZqQ3mwVhbi0siDeWwVVaa0ojrTsSZjbm2rLbR2pQXbdvyX7XwIdCgR1QPHUGuLM66WJdkAullky0srr7WeqwlhN3bvgHug9OQj0npUjD6wl7qPXvJZ8RHkGkPOAgK4bDIQsn4eWH%2BzIAHchwYKFTkoOQKcYcQ00GDHQ6fvoJ2zlDzOIO4Y5/kLnAu%2BekfWJsEjXG1PkYFaymjpWZV9Yq2FiLSq2PRYa1x7VvHSD8cE5QMjGmtNhZkzGfwxybmBFk/JszlHBUfK%2BXZlrjn4DOfBWKzr7XiBeZ2L5mVLAFCWTxZZSraZJjEqi2SilDLp20okCDxlyXwc6BAMEDLWXeXS9y/b4VrnxVUElf7wPwfQ%2BWkmDV7rdWEgNcCM1z7bXK/Gs943tVIAg9CKtiH45Vsw8ECtqoTFQ27WjYgI61l03Jstonz6v1Oag2LcEOGyNgr1vxrEFtltO2M13dTQd3NePWUnfMmdltF3WVXddbdht15Hu8Ge521k72%2B0Oa%2B0wYdo7/stsB3HudoOk9LtTyhzXXPRsCrTvSR0PU4F2FdgxwvSvQSBvTx13W52fWJ1fU5z0E/QqHA2A2pyaFJxAyZzQxwJwwaCg2aCwwwNIL6Gg152IIIwQ0oKF0YIWHoMpyIwlzpRy1l3eU4ELyxQDyDzuC715F7zV0jw401W1wcz40wAEzGGE3uSNxABOV5ECECH8AuTM0U3UJjAMztzl04Ed1%2BR11E38Ak2uRjEU32UkDOS4EOTMFSHuUCB4OoyMPs11TIyJQMN4Js2dzWDbSyGcEkCAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/repack/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/repack.test.hpp)
