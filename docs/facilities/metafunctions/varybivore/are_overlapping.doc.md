<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreOverlapping`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-overlapping">To Index</a></p>

## Description

`Varybivore::AreOverlapping` accepts a set of nonrepetitive variables and returns a predicate.
When invoked, the predicate returns true if the list created by appending arguments to the previously provided set contains repetitive members and returns false otherwise.

<pre><code>   Vs...
-> Args...
-> Vs... `overlaps` Args... ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct AreOverlapping
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

We will showcase three examples.

Check whether `1, -1` and `0, 1, 2` overlap:

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = AreOverlapping<1, -1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<0, 1, 2>::value);
```

Check whether `1, -1` and `0, 2, 2` overlap:

```C++
static_assert(Metafunction<0, 2, 2>::value);
```

Check whether `1, -1` and `0, 3, 2` overlap:

```C++
static_assert(! Metafunction<0, 3, 2>::value);
```

## Implementation

The name `AreOverlapping` is probably a bit misleading.
This function used to be a helper class for `Varybivore::AreUnique`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

After instantiating the first two layers, `AreOverlapping` has two lists of variables to work with.
The first list must be a set, meaning repetitive variables are prohibited. The reason for this will be apparent later on.
For the function to return true, the second list must satisfy two properties:

- Every variable in the second list is not contained in the first.
- The second list does not contain repetitive variables.

To check if a variable is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'variable' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, variables in the first list must be nonrepetitive.

We will implement `AreOverlapping` using recursion over the length of the second list:

- **Base Case:** When only one variable exists, the function returns true if the variable is in the first list and returns false otherwise.

- **Recursive Case:** Pop the first variable from the list.
The function returns true if the variable is in the first list.
Otherwise, we append the variable to the first list and pass the result back to `AreOverlapping`.
Then, we invoke the second layer by the popped second list.

Here's the entire implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...InspectedVariables>
struct AreOverlapping
: public Vay<InspectedVariables>...
{
    struct Detail
    {
        template<auto...>
        struct ProtoPage
        { using type = void; };
    };

// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, AreOverlapping>::value, 
            void,
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgABwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGZwshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIJBfz2twAakxEV9DkCCJgWGkDFS4W4mF4iMTWngmDF6DiQRNiF4HKzEXiAhZbnNHMhbmgGBNMKo0sRbkyWQA3MReTCwkUk4jszmYEwBe5w0WG41gqxXfFHW5CBDMgj0ckHSnU2lMenw5WoAB0fu5V15/IItvtBEdBoteN%2BANjgOtdwAkjT6GxBB6cs6zgm43GgSCqSmPZHGczfX7EzLng5MOgdXr6NiwbjA%2Bjg7dLsRMAB5FXxAxpNLhYAgkC3NJeTl4SUkoXwysKatUutsjmNnF%2Bn3Cy2XW57sVtgWPFp0EH7rU78/nwvuz2loibgO7q97oMC5TEVBEZRMYAGq4vnuhqil4WRGLcSLPLCYL3LcKqoHg6Amlq5qXvuZomtG1w7LcABKmDIBsWR9rcjJKCAZ77jedIlt6twLkuw71mumCkEqZabvhEzMfqTYts%2Br6HiGH5fqgP5/pRQEipJV47DhJjJBox6YrQCkaLcADudC0AeqBpLcXaEcQWQCGxTDIAg7wqsOYoICQBAALRvJsXiEFuAGAaBNmQZqcKwRM6AgCgAj4I0YgyeeDIRYBAVBXgCgojETBKCiqBUAys4MgxBGOEYPFcs2pCdj2fbEAOQ5GDiQVqt4rGwh5gH7spdBsdFL7Fb2/ZMIOw5ZVWOW1vlHybmx2UOExq76k%2BjVVSAPlBdRxa3CJ36/iWXEEENCiPs2C3IpGO5tQeGaStKsryoqMSoJ4cHqr5IqxSA8UogorCYCiKoMj5bHwYh3JGphDUoYDwK/DhFjJZqZHsDJi13nRY25cAQ3Tfub7CZ%2Bq0SfO/XjXlk0FfxkXSUD55eeBPnQf5BCBcFDChTk4Wk%2Bh8JHeej3PUlKVpRlpJ9YuOUTbqLE4mxHWleVvW7SANUaq1zMvr96CkGz%2B52g6BVuIjg0E8NfqjbjSMo82R2zT5IMzQrx0SlKAjnQqtxXTdsv3RYDBfgetPPa9bAfV9%2B0/QhSEmwDUZAxhYegwJEFujRDLepuW2o3u5PAMta1U8tmNiWtvPC7xO24pHEeHTGuaxkCBK3AAYngxkhtgqisLSmrfDm5enPmZcHLcACymAtFQXgMONAhZq6RbwxxfqdsAfEgqnfcD0wQ8j40mfi11PWVfCXBsQ5XBPkF4klrP23%2Bibxfd4SAAqHwhm3rYnSiyVKG0ED94Pw%2BjwwDIaGxe9bhmFmi7ZYIN24dxOJXG0QgCIhVuI3ZuTpH7XEgQCLulxxTThfgoN%2BBAP7L1Xj/P%2BbEzCkJAXdMBV9UFoKge3W4N9LLEHQAgpuKZW4UggbQ7MVon4ShwXgiAYAwBLy/mvHIJDbhgnIdLUBJoOCrFoJwAArLwPwHAtCkFQJwNw1hrBinWJsXy4IeCkAIJoBRqwADWIBlGSB9BoRIZgzAAE4XFcGUY4xIXAAgBGkEojgkheAsAkBof%2B6jNHaI4LwBQIB/7mI0Qo0gcBYAwEQCAdYBAJwEHIJQNANI6DxEiG9TgqgUgOWSJIW4wBkCSikD6MwvBayEBIIhPQ/BBAiDEOwKQMhBCKBUOoRJpBdB7w0hiNInAeCKJUWoixWjODdmZNk24aVbhlOSBUqpNS6n2LMLcCAHgCn0EVOYMEXBli8ASVoVYEAkD5KHCc3JEAHmFISMAKQZCaC0CpMZSgMR5kxHCK0REUzeBAuYMQRE3YYjaBymC0g%2BS0wEG7AwWgoLhlYBiF4YAjJaC0FidwXgWAWCGGAOITFddBZ9kJZouUBFmTbFMeEKkATNG0DwDEDEUKPBYHmeiPAISiWkFKldJQjxSVGA5UYCxqwqAGDnkSd4GluzPHUaYjpwhRDiF6ZqgZah5mjP0GSlAejLD6E5bEyAqw9KNEJQ5AKflTCWGsGYSJpVdRYCtRAVYdhBbOAgK4aYfg96hHCMMKoow97FGyAIYNegY2NAWCMBIe8/U/36FMTwnQ9DpsaJmwY4bFhRtsJMdo2aChprLcmyNqbfWGK2BIGZHBVGkAibwKJ6zymVOqbU249T9kQFwC005JjLlmNlasBAmAmBYASD60gNjJBgh9C4sEfiNCSDMJIRSGhlHJBcfoTgQTSAhPOT6ZIXBkiJBcd45IdiPFrtSO2hZ0TbBxInYk25aS7kZOWcyZ5ryTnFLYJwVoLAVQBAckwKUBhwJcBcT6LgDimmhVaYFPemquk6ukHqpQBrhm6DIeM7qYLm2tpfVEpZWTmSrKoF2zZPaoRkv7Yh5D6lDmoGOfEWE4IzDjuuUk39QH4iAa4480YzGjAIa4P/b5vzYkQABcMiFIKEWqahTCuFDgEVIsYCitFGLNFYpxXiglCKSVkopcZql40aXzPpYRKkCKWX1HmRyrlILeXbE0QKoVpjRWZEwBKqzw5ZV8AVQoJVmAVVqoRVh7VPTcOyH1UMzRRHjUyudVYc1HnvU2rSHazgDqaZOrNRYN1HaPWIQ%2BPAX19R/V%2BEDfTeNob6Y1qWNGzIsbcgVpDekbrSai0ptzQ1jNZbWs9EawWjrJa5hZvyP1%2BbhaKgjYuWsDYjb1sBIo/MztGytmwZYwhpDDiDnDqIKO85AnJ2kGnbO0YC6AknrPYhzdARlEuN8WCLdO7JB70o5wGJH7BPfvgL%2BzJ2SxPceICB7Y4Ge0sAUCqSUKoTs0QmKhkdbTMOyGw0lvp8h8NpZ0CAaRJHJlEvI3M4ZVH/0hjWaoRHyPUfo%2BLBMA5RyJNXbBDdr9yT7nibedD7nMtkCDg%2BghlEGOCAoiZ7hugCn/mAuBVC9TqvoWwvhcKvTghUXovmSZ3FYhzPCss1KnzxLbOOHs8MxzjKXOCDc8Mjz3LETef5bqfzvBAviupKFmV/P5W/ii8q1VjB4t48SxIZL/TieGrJ5l4w5WLUxHy1owrORCU7Fitl117r4ietq9aqbP8XAtb63oMNq3a0JsGzkSbiacizdTaX/NE3K9prG%2B3%2BYw3a9VoGJN5bLem0baMaPnbNPImcHWczlHcE2dUg50OtDV2LlXNu/dudlBm0vZAK4n0YIwTKM8f9sJR%2BAjXrbXtoH774m3aXco1dPiAhhMSJIdxXAnFmFSAEsEU%2BO1b9Qdm1Glr9acgDbtSoTIuggA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_overlapping/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/are_overlapping.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_overlapping.test.hpp)
