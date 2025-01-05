<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Has`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-has">To Index</a></p>

## Description

`Typelivore::Has` accepts a list of elements and returns a function.
When invoked, the function returns true if the previously provided elements contain all its arguments and returns false if otherwise.

<pre><code>   Es...
-> Args...
-> Args... &sub; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
Has
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct Has
{
    template<typename...>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Examples

We will check whether `int*, void`  is contained in `int, int*, int**, int**`.
Then, we will check whether `int, int**`  is contained in `int, int*, int**, int**`.

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = Has<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(! Metafunction<int*, void>::value);
static_assert(Metafunction<int, int**>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for `substitution failure is not an error`.
It roughly means we are going to create an `if statement` for template instantiation, where the condition will be the legitimacy of an action.
In this case, the action we will be using is accessing a function in an overload set.
This action will fail if the requested function signature is ambiguous.
We will use this behavior to check whether one overload set contains the other.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
It is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

Since arguments are not allowed to have the type `void`, we declare the parameter using `Element*`.

```C++
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
template<typename...Elements>
struct Has
{
    template<typename...InspectingElements>
    struct ProtoMold
    {
        template<typename, typename>
        struct Detail {};

        template<size_t...I, size_t...J>
        struct Detail<
            std::index_sequence<I...>,
            std::index_sequence<J...>
        >
        // We create two overload sets and combine them through inheritance.
        : public Label<Elements*, I>...,
          public Label<InspectingElements*, sizeof...(Elements) + J>...
        {
            // We bring every `lark` from its base class to the current scope.
            using Label<Elements*, I>::lark...;
            using Label<
                InspectingElements*,
                sizeof...(Elements) + J
            >::lark...;

            // We will do SFINAE on the second parameter.
            // The default argument `void` ensures
            // the compiler checks the specialization
            // before the primary template.
            template<typename, typename=void>
            struct Hidden
            { static constexpr bool value {true}; };

            // We ask the compiler to access a `lark` that
            // declares a parameter of type `Element`.
            // If the compiler can access the `lark`,
            // this specialization will be used.
            // Otherwise, the primary template will be used.
            // This function checks if both overload sets
            // contain the same element.
            template<typename Element>
            struct Hidden<
                Element,
                std::void_t<decltype(lark(std::declval<Element*>()))>
            >
            { static constexpr bool value {false}; };

            // This function returns true if `Elements...`
            // contains every element from `InspectingElements...`
            static constexpr bool value {(...&&(Hidden<InspectingElements>::value))};
        };

        static constexpr bool value 
        {
            Detail<std::index_sequence_for<Elements...>,
            std::index_sequence_for<InspectingElements...>>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQAcpK4AMngMmAByPgBGmMQgAJzSAA6oCoRODB7evv5BaRmOAmER0SxxCcm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfFJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLMAGZwshvFhriYQW4vI5aIQAJ4w7BA8xghgQrxQmFuZBjdBYKio9HfA7XEJMOK0D77AEETAsFIGRl4ghIx7MNjXbD0NiCUjXDIAL0wAH0CNcAJKki5jYheByU6m1dEAdgswqajmQ1zQDDGmFUKWI1wAbqg8OhrgZiABrCB8pmMAiLGFakzq24esmXP4B/5An47GXM/mupj1Ol7AEhwN/AFAxnhqOYdmcxisTAAOjzzoFBAUcvOCqVUoAEkxixcvVYLtdG9cUyy0xmudm8znpYbHg5wsAC67iyC0Q2m2XlcpiKgiABZTzoIFN6Ga5crpst1np2EcjtsIV7rNsEsbicERXK%2B5NOirqze3218dnrdt2GiiUELvSoUfyVdgApU8z21S8pWvJg6DxdcQPPdAQBAcIsFUcUlAARy8Z4dzcaUu1RUgYNg7V4MQhhkNQzAMKwvEALw0dCJXYCzy2LZrgAdUwfViEwNNmwAd1Qa5UHNeJaFQJgbSUItrkMG00AqcJOIIBAmWbBAZy8YAEGucIVOIQhDA2HMGKbEBrhSLwYkRPUqRpPEh0EBQdiFWVRy7AjnxAiyrLwGzVVoPEewUPtHCMByi2c4U8DFVAqC7J0I0cxZoUsa4gLcvMTMbOsso3Fj2M4mJ9KMa5MBE4gkWhAA2DQ7XtEwauuKgZxYHTpJiatOIhat3iINSurWbjBGFNBHmMzzYK8DIStstVYXCpyXNRBC6ro%2BtziIpspoHFU7NhXLYKCkKBwW5yDpAj9YvihbkusNLzuy0cVuae01r9TbG3yjjrj4uhaXQQShAAMWlSJzmwISGH64VMANG0UmabNGWIcaNo%2B/KABUVOuYkmC8WgpWaYAfFdaqNEta0Go0UrDTWN4HuufLlK61BmToeJ9RU5B7V67HgthvAxGiqMsgZ/K4n4bjodNPAWGaSrX0ZVGPubJlWzZXdM25TBDy17MYVuCml3oiaLovctrgra0sAYBm621EW9QNI0TTNGJUE8C0xEwu9zfTB8QU9AP1rF1jvure1ofklJ2bNPqmGQDYFHeJgybqqm1KjUOcdhu03hk8zEbYZGhKoZtMzJ8KqeV9HWOlMvmf1VmY/oM1RChhOk95ziqfTmqPLRzamYQPB3n5l4hZFEWBB%2Bv7rjia4pswdAa6H1iAHlmeIX6lEPbGZblirVdTRlZ9oWkF6Xlfs6x0emq8LFo2QLmeZ0sv3eUoTyrEiSYaLbODQ3iho3BQ2ZSqJS/AzRW2Ejza15BApiRFJyVmtowaCptNrhQHirFchIEJG0lHiLAEIjwQDqhAPBIBiG0HNGIeyECdioggIsFhiDYJsJAvbGYuom6GkZK7eeHtaS0O8D3TUVAxBKC9D6QOq4ZEhwwXlVit93hUAfv2Ge3ECBrENM2RUnE8BlypgtPCNUAGyEgrosq8RKq1BdMNZqrMyZHVhqFQcECFCmI0AzbhvleEu1NIIz2IifZ1ggHhMwVVzBVQgFbIkaDYQuP7GFDxy0QAhMwKw4OuVpGPkBIo3xTsBABLdkIr2ojoSKJyoolcEEoLvgICRJCxoKJUSxBKSW9D7FFjotgbBH1KHNJQuhTC7TxSdMSb2VxJ0PG9LSRknJ2TPK5MDu9TcattztmPLmPM5xgDcW6SOMcg9F7TWANcBctAbQG2uNOWcqBLnGzcHsg5hZPGZXoqsp8JzoFbO1l2c4xBgBHMIoU/x/DAnu09o88U5o7x3PnIuPEgLgW9Pwd7f28iNRYu%2BfGBMcYKTYFUKwFknFPjBgTEGXFFI5yYCaGox%2BWQYwnGTBst8bhYGdl2UCkFFxtolVpfS9R0YblVhHG4cIBAhSSsijK2Vgg9glgQo85FPK5lfPyf6G4GM3jSXJfKHUvlxQ9XiAQCAYAwAXLpUwBlGjbawhlUKI28yMXug1YU41ydTUQEFTa4VosHWCh0gqxhT10muo9BwZYtBOAAFZeB%2BA4FoUgqBOBuGsHdBQqx1g91BDwUgBBNBRuWPaEAsbJA5g0AEMwZhEiJC4LGqtAQuDqnVNIGNHBJC8BYBIDQGhSCJuTamjgvAFAgH7YWpNUbSBwFgDARAIBVgEAslKigEBo6x0iNmTgqgAhVQALRVUkNcYAidrhSBzGYXgy9CAkGtHofgggRBiHYFIGQghFAqHUFO0guguCkD4sQJgKROA8GjXGhNRaU2cHXvCFdpdri7oPUek9Z6L1mGuBADwbNW4pRBFwRYvBJ1aGWBAJAG7W7kEoBR4YwApBmD4HQZGY6IAxCgzEcI8tQO8A48wCq68YjaFcdx0g8lCzrwYLQJEUGsAxE0m4MQtAx3cF4FgOWRhxA/vwNxfsIllPJuNLDeEmx82StqFBxERV5YeCwFBi8ssRPlXdkoe46ngCIiMEW5YVADDAoAGqvD4uvLkInH3CFEOIN9YXP1qCg3%2B/QhhjAZssPoPAMQx2QGWKgFI9RlP7sJAbUwlhrBmCHeVfSWAMvMK6NM5wEBXCTD8P%2B0Iil5jDH/YUTIAhGt6E6/UOYQwEj/rsLVho4xWieHaHoEbdregtAGxUdrthxs9eG%2BNhbCwCMrDWBsCQ4GODxoHVB4diG92HuPaevU6HMO4FvWaDEBGiNeeWCpCSwxqulskCCHMiQQRto0JIMwkgaoaFjVVRI%2BhOBdtID2/DOYqpcCqgERIzaqrlobb9qqR2f3DtHeOgtXmZ3zrI4uuD8IqPrubpu7dHBmgsHNOqfdqduolS4IkHMXBK3XvwEQCrD7ZDPsi9IaLShYs/t0AxwDwHuP7cO4O3gw7YPLvhAhpD539QGFZ%2Bzzn1MsNU9wxiMwhGCdTtI%2BR/X8QKc0YSCzuj9b%2B00AJvEFjbGf28a4yp0g7v%2BOCeE57sTroJNSZk5gOTwAFPn2U/mtTiXNPJu09MvTUHDPIGMyJszHbk2WaAxVGzmxk32Z7Z7pz6RMCudjwOQnPmmD%2BcC8FxgoWBcRdfcL2QMXv3JolwlzzRWrApcs1VrLOWsh5YKyCW4veStlfiBVt48BlgzfqC4Miq3ghkQ20tvrWRV9b5KK1wb027GzZW5NvIw2j/1Dm/0ffi2hvLb6KvmY82b%2BbYX9m3bW2O1y%2BO5wU7yHj227nra6Vo3Y84kB4aPYm4kYvY8RYAJDVYdrQ6w7s4A7qixqJCtogiA7A6SD/ry7QYjq2D47EbTqzoLpLorpW4W7EBbpsCcB04oYsAKDmh6jmhs45jbhjDc53b3r/phaC4t7vryCi4d46AgAggAZAYgYqay6QY44wZk5SixSIaMHMGsHsGcFSh644YcwYggjG4kFm4oDUFUE6EJAsEpApCwps7iiaHiiqBHqMZO7EAu7sacYVQibe5IgCZCYOAiYB6CBB7SZaah7yaKZR6qZMix756qZ4A6aOBJ4/op5p6e4Z4WZpY55Ih552b6RF75ol4uZREaaV6m58C%2BYKABaYBBYhae78HN4SCt4foiFxbiHd5JbFb95paD4prD7FKcBbB4KT6WClYK7lbWhz6ZY1Z2rL7uCn5NZr7oAb53677ZBzG9bpBdYMBLGH7dACBX6P4X49DrYv5LZP4Ta5DzFnHbFbZZo7avqyHY5Dq/4OHHpMEsEWgaFphjCgF3YQEGHPakCvZwGUD7ZIEgC1o5ggggixqNq4F9pQnqhI6PEK6cB44ToAmfaxo/Ytrqh9oBCSD1pcDVqRKQ4cAghyFPGEGGH7ZXrIkEFPam7LDlQZDOCSBAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/has/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/has.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/has.test.hpp)
