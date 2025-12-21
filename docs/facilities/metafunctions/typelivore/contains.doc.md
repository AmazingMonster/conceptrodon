<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Contains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-contains">To Index</a></p>

## Description

`Typelivore::Contains` accepts a list of elements and returns a predicate.

When invoked by an argument, the predicate returns true if the argument is in the previously provided list and returns false if otherwise.

<pre><code>   Es...
-> Arg
-> Arg &in; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
Contains
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct Contains
{
    template<typename>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Examples

We will check whether `int*` or `void`  is inside `int, int*, int**, int**`.

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = Contains<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

`Typelivore::Contains` uses `std::is_same_v` to compare elements and a fold expression to combine results.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Contains
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {(...||(std::is_same_v<Elements, Inspecting>))};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/contains/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/contains.test.hpp)
