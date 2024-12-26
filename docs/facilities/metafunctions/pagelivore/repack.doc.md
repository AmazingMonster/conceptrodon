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
/**** Sequence ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

/**** SupposedResult ****/
using SupposedResult = Sequence<0, 1, 2, 3>;

/**** Result ****/
using Result = Repack<Sequence>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7kIEIiCPRvkdgQRMCw0gYWQSmIjUAA6fnk66TYheBzU2kEemYOFWa6g/6AxWHYEKu4ASTZ9DYgiYTUZyvlSqN5wpVxZmt10vh5vZlq5PP5vPRdyhTAUXwA8i9iLqcoKrsLRQQ7gAlZ5MZAAa0xAHZZSDrnck3cbRyrW4CCiXsw2I7/cm7oGxU9WnRYXGTDGHjLTbtdncLG7MHc3E2QKaC6m7dbWbbOfDuUQ84FsC6DO7qZgAI5eN6YUh3Qd8/kANTaeCYsXoCnzyaLwZLTDoBKE09nOPTa%2BIG63n2HGJHoILlfjBYLXiyRhTWebcIedy9BJfQEAkrxvbd7xrRNk0ratAnjJ9ky7fsM17NMCUzbNWHnRcHQFEcxzdL5TxnOcF0wxhsLuAAVH8FyXR0wM3bddyTfdHkwUtaBPM85wJWiXgXJjbwUSDH2gpMX0Qt87g/CJgG/F5YUCf9AJ9JpQPXZi73wh9XxgqsoITG56zDZBNiyAA3ZtWyUds5QklM0LtRyCWkt9kPTBjdMIicSPPbYrlIdzO2clDvKdAjXT83iLxsELkwi4T6ADBcEqTJKtNvCwFGCxzOx/HNMEdD0CAQBId1c8SrgLdjD2PeF/LnEF4WSzAA3vBcmrizTr20nLOoAsqKsg1yK3y5M5K/CjlP/eruImyT4XSt8aTpehevA9rRP5ISsvoAbdLymqZLfUryuIHanUW5TsBAEAKKM59DPgjskLC6UqrcFbPIwwrsPovDItHaLiNiwLjtOpyLRQiiisBocfNBydSLiyHTrhqjqKCn7/rYGj4puzK%2BtvVLYSJoG2py9GZMx3N%2BXOir3NYwsCBFYtOKPbjGvB9r%2BKCu42o6o6UYCzArHhaibEF/bxau9EF0Zy7RpOyTxtVt8poUma/w4riVrcm7aoIdB7oiFlgASAB9JRUe2Fbn2Wo3TuJe6WCYSNMBtvBgEidArYIAlXZALIAC8vcDkcaaht95kcZArdESYg5Nt2Pa9rJfcwf3I7cYOw4j8kRwgIWFBWR1o5jvdWnjxO3Vz4P3c972s5zlPTZDvBw4DovsBL2WcvLgVnaW7BK9OpX5Zu9F7se16xrghDHN%2B608eK/llAjT30G67Yd2q99PwUgBZTx0FmvWuYJTeo2z3edOB2efyM2CX8pY0mUNe5sFUVh2WbH4X8P4mgcjcKk999QgLNB9duadm6Zz9j3eE%2Bcu6FxHI6K4xBgD7wxNcYgZ48D4K%2BBAAuqAqCOggJg7BKxZq60kCsUE7F75vzAfcIQXg0jFGzmGBQXhaDBkAdcLW1IOFcPQDwvhwZdbMPhBoBcXAFxmAXIEIuS9WGHFDJ8SRkDgTCIkfwi%2BYY0hbx4nbK0uCrj3VPrQdAmInYa2DubTAltiA215gSc2C4NAK3Jg41OIAIhYFUG4sxBIFF3DMArdyjiGBBJCWLAkKjqqqNrFSainwBGfyFDXPACciIJAICQ/xChsJWzdASfRBAuqiMyNwrR/D0QMPghwNYtBOD%2BF4H4DgWhSCoE4N9Sw1hCwbC2L%2BcEPBSAEE0C0tYkYAiSF5BoAAHGYMwABONZXB/DLKWVwGMMZpBtI4JIXgLAkhyK6T0vpHBeAKBAHIqZ3SWmkDgLAGAiAQAbAIGkRE5BKBoDZHQBIURsKcFUEs5IABaZIkg7jAGQMgO4UheRmF4NnQgJA8CmwUfwQQIgxDsCkDIQQigVDqCeaQXQCiADuPo0icB4K09pnTpm9M4B6REPzgxkLuOCqFMK4UIqRQsswdwIAeEBfQYgsJxkrF4I8rQawIBIABWkIFZAKAQFVeqkAwApBKJoPwiqlBYistiBENoKIGW8HNcwYgKIPSxG0JgBw1rSAAu1AQD0DBaBWopVgWIXhgCtloLQO53BeBYHdkYcQ/rCEuscNZcNPTMCqBdYiHYEynFHJ6ciWIPp7UeCwKytmeAzkRtINZYgsRalPGjcAZERhplrCoAYbBK4PjUsAl0iZuLhCiHEESvtpK1CsqpfoQwxhrDWH0HgWIdzIBrFQGkJo4bIXEj/KYQZlgzBXKrdeLAC6IBrDsAmnILhYkzD8AosIEQRhVDGAo4o2QBBXr0M%2BpoixRg1F6GegQAxpieC6HoU9Dh%2BhTCGHepYj7bAQbfQo%2BY7Qv0PpqCekZ2wJBMo4B00glzeDXN5RC6FsL4WIuRaKiAuAMXSqxFwOVkzm1rHKkwLAiRj2kDmZIQIvI1mBAORoSQZhJDJA0BofwyQ1n6E4Cc0gZzAhcF5MkLgyQllrN2ckfwkgtm8dSHhtlNzbD3IY08pV7zlWfM5b8zV2qpUgrYJwNoLBLIxkhUwQiX4uBrN5AplN%2BAiAHr0H2/Fg7pDDqUKOiluglG0qYPSiNWGcN6euRy75iI7g8r5cR9zClPPecWWKiVaqpUysCGYejCrnnmZswkP5WrUCSrGK6Iwnnah8DoCyS6JqzUWvtW621lrHXOtdRWj1jAvU%2Br9T0gNQaQ1hrdVGydsapvxrA0m1lqb00sjddm1leaC0oiLTsHppby0TKrTWpQdbFvyWbXwNtCgO2YC7dmN1QWB2EtC7IEd5KelRYnU2rdVhLCzvnfAJdK6chro3SpQH1hd34f3Viz4YPf1gecBAVw8GQixOQ8sJ9mQX25CAwUfHJQci45g6BpoAGOjE%2Bvaj6nEGKc/sQ7T/I9PWfM8w%2BsTYGG6NSewyyilBHMsCqazlrzPmxVUf8yVuj8rGOkGY6xygWGZNya8wJmM/g1n7MCIJ4TWncOsuubcozFXTPwHM18rltXqvEDszsRzAqWAKEsoiyyuW0yTDRX5zF2LiX9oJRIT7JLws/Z0CAYIMW4uMoF4lk37LLPcqoLyl3buPde8tJMAr9WisJBK4Ecrt2qt5/VXbsvUqQDu84VbT3ayrbe4IFbVQMK2tGs6xAU1FL%2Bu9Yrb3h1TqE1utG4Ib1vrWXTeDWIObFaFsxqO5GlbibkcUo2%2BZLbFadsUr25aw7Jbrynd4Od2trJrtNpM3dpg7bO3dte7IYLH3A/fbHVH/7U7t02DzUe8Hq7OC7Fdlhx3T3QSAPWR0XQZ3PQx0vTpz0FvQqG/XfQJyaCxw/XJyg0QIQwaD/WaDg1gKwL6H/SZwwJQxAzwPZzIIWBILxzQ150JQSyFyuU4DT1hVd3dzuHr15Cb2lz9xo1lQVxMyY0wBYzGHYyOXVxAHWV5ECECH8G2S01ExkJjBU2N2F04DNweUV0438B4z2RjFEyWUkE2S4BWTMFSCOUCEYPw3UOM0VSw1RVUKYIMwtzWCrSyGcEkCAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/repack.test.hpp)
