<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::LaboriousPress`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-laborious-press">To Index</a></p>

## Description

`Omennivore::LaboriousPress` accepts an operation and flattens its inner structure. It returns an uncurried version of the operation. Check out **Examples** for a detailed description.

`Omennivore::LaboriousPress` functions the same way as `Omennivore::Press`.
The only difference is that `Omennivore::LaboriousPress` has more base cases.
This function is provided to compare against `Omennivore::Press`.

## Type Signature

```Haskell
LaboriousPress
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename>
struct LaboriousPress
{
    template<typename...>
    alias Mold = RESULT;
}
```

## Examples

We will press the following operation:

```C++
struct Operation
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage 
        {
            struct Slash
            {
                template<auto...>
                struct ProtoPage {};
            };

            template<auto...Agreements>
            using Page = Slash::template ProtoPage<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

Note that the type signature of `Operation::Mold` is as follows:

```Haskell
Mold :: typename... -> auto... -> template<auto...>
```

After composing with the instantiation map of type signature:

```Haskell
Instantiation :: template<auto...> -> auto... -> typename
```

We rewrite `Mold` as follows:

```Haskell
(Operation::Mold) :: typename... -> auto... -> auto... -> typename
```

This interpretation indicates that if we pass `int` to `Operation::Mold,` we obtain a metafunction:

```Haskell
(Operation::Mold<int>::Page) :: auto... -> auto... -> typename
```

Then, if we pass `0` to `Page`, we will obtain another metafunction:

```Haskell
(Operation::Mold<int>::Page<0>::Page) :: auto... -> typename
```

Finally, we pass `1` and obtain a `typename`:

```Haskell
(Operation::Mold<int>::Page<0>::Page<1>) :: typename
```

By 'uncurrying,' we mean we would like to pass all arguments together via a tuple-like structure.
The type signature of the resulting metafunction will be like this:

```Haskell
Metafunction :: (typename..., auto..., auto...) -> typename
```

Since in C++, parameter packs are not transportable notation-wise, we place them inside suitable vessels, which will yield `typename...`. Since `typename...` corresponds to template member `Mold`, we will invoke `LaboriousPress<Operation>::Mold` with the results.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Operation
::Mold<int>::Page<0>::Page<1>;

/**** Result ****/
using Result = LaboriousPress<Operation>
::Mold<Capsule<int>, Shuttle<0>, Shuttle<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `LaboriousPress` relies heavily on recursion.
We will showcase a simplified version that handles `Mold` and `Page`.

```C++
template<typename Operation>
struct LaboriousPress
{
    template<typename...>
    struct Detail {};

// Base case:

    template
    <
        template<typename...> class Container,
        // There is only one parameter pack left.
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    {
        // We invoke the corresponding template member of the operation
        // with the extracted pack.
        using type = Operation::template Mold<Contents...>; 
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

// Recursive case:

    template
    <
        template<typename...> class Container,
        // We separate the first parameter pack from the others.
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = LaboriousPress
        <
            // We invoke the corresponding template member of the operation
            // with the extracted pack.
            // Then, we pass the result back to LaboriousPress for further invocations.
            typename Operation::template Mold<Contents...>
        >
        // Unused packs are recycled for further invocations.
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = LaboriousPress<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/laborious_press/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/laborious_press.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/laborious_press.test.hpp)
