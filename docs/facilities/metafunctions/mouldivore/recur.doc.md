<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Recur`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-recur">To Index</a></p>

## Description

`Mouldivore::Recur` accepts an operation.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function instantiates the operation with its arguments and uses the result to call the operation repeatedly until the result satisfies all the predicates.

<pre><code>   Oper
-> Preds...
-> Args...
-> (...&&Preds&lt;Oper&lt;Args...&gt;&gt;::value) ? Oper&lt;Args...&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt;::value) ? Oper&lt;Oper&lt;Args...&gt;&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt;&gt;::value) ? Oper&lt;Oper&lt;Oper&lt;Args...&gt;&gt;&gt; : (
            &vellip;
   )))</code></pre>

## Type Signature

```Haskell
Recur
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Recur
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will increment `0` and `-1` until they are greater than `9`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** AddOne ****/
template<typename Val>
struct AddOneHelper
{
    using type = Vay<Val::value + 1>;
};

template<typename...Args>
using AddOne  = AddOneHelper<Args...>::type;

/**** IsGreaterThanNine ****/
template<typename Val>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Val::value > 9};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Recur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Vay<10>;

/**** Result ****/
using Result_0 = Metafunction<Vay<0>>;
using Result_1 = Metafunction<Vay<-1>>;

/**** Tests ****/
static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will implement `Recur` using a helper regular function, which utilizes `constexpr if` statements to decide whether the recursion should continue.

```C++
// `Sacrifices` are the arguments that will initiate `Operation`.
template<typename...Sacrifices>
static consteval auto idyl()
{
    if constexpr 
    (
        // `LessonsLearned...` are the predicates.
        (...&&LessonsLearned<
            // `History` is the operation that will recur.
            History<
                Sacrifices...
            >
        >::value)
    )
    {
        return std::type_identity<History<
                Sacrifices...
        >>{};
    }
    
    else if constexpr 
    (
        (...&&LessonsLearned<
            History<
            History<
                Sacrifices...
            >
            >
        >::value)
    )
    {
        return std::type_identity<History<
            History<
                Sacrifices...
            >
        >>{};
    }

    else
    {
        return idyl<
            History<
            History<
                Sacrifices...
            >
            >
        >();
    }
}
```

Note that we wrap around each result inside a `std::type_identity`.
This is to avoid creating an object of an instantiation of the operation, as it might be impossible.

Here is the entire implementation.

```C++
template<template<typename...> class History>
struct Recur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    History<
                        Sacrifices...
                    >
                >::value)
            )
            {
                return std::type_identity<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >::value)
            )
            {
                return std::type_identity<History<
                    History<
                        Sacrifices...
                    >
                >>{};
            }

            else
            {
                return idyl<
                    History<
                    History<
                        Sacrifices...
                    >
                    >
                >();
            }
        }

        template<typename...Sacrifices>
        using Mold = decltype(idyl<Sacrifices...>())::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3AQAJ53AD6BGITEICkh2H%2B/0%2B3xx21%2B2IuAEkWIl6GxBEwaq8dvjcXTDpjTgRMCSDMzIdCWaTKZgObC7sw2AA6EXoi6gpgKF4ACTwwxIMPR/2GxC8DguACVMMhlpiAOxWU4XY0XZmsnl8rls3lQ/mMViYEVCsUSqVOgLPBQCBQehohdBKo0mlVqggXZTEVBEDWoJgBoPGkwG/4m1Omq0W21w%2B3CkVCJjIYh4GirNGAjEJtOTRzIcXe5kANzEFyYXiIFzw6BhtAgcxTacTycrA%2BNxbrDGGmFUiWIEOHI4g/ZHI/W6whADYNB6pd7fcR/U6TJuW8RMKaEGeZ5h8KJmQpnfPl8aIIezOvzOvt16J3v/Ryl0%2By6rhuGiyvKxCKsecrnmeqB3MiVIEAglIXAA7nQtAXKeOrEA%2BJyAYBYFEBB/6PgRA75oWxZ4KWh5keRgb4eRJroiAIBNt4mB9vRJrcUxgFJoa/HMaeBDLAwFzDOgbF2vCnaMI4sIckRCqkcJzEjpRRYls8dHqQRSrloJSZXJCQkMXqpk8Ym1kXFUSgdlQ46TtOs4Acui62amL6im%2BH5frumB%2BteakaQOKkkVC7lhRFipRV5BFadRtGiglA6MWFaYZWFrHsWIXhcdFA58RZ5lhaJ4mSQQ0kgLJ8mCIQcVuLFoWZSaLXxfpbUXElOn3qlXXMdlGmGRiyaWWZRVZRNpxTam9m8rZxlpVhmBifuHZdrQrXdR1bhzQRe0HRpvU0bpA3dYmRkramw1DeWvaTUtM2DSZjKDWa3LslmAoOk6p2lndqZeKkRgXAAsp46AQoCVwXFgoJ2hAnbdhyAPnc6D1zHMMnZk9wlvYCQkAZ91qWua33QtmgqOqK5bigYboiicwCniyCllhWwkg8EwCarG0OQnDEZRqgMZxhyLNs%2BSBD9ZjGJE/qpmK7NHz0m8WK7Bc2CqKwpJnhravq3i73mMCDCgl44IcmgFu3LLjGa5cABqTAwtSJtMhmlOtu2hKMSG6qu4qs0GlVlI0c5zKuS2baoBcHEFRCBr%2BxNRPJ8rxNG9sFwnOg6AAPIhB7DJexTNpU79bAXK723XScgdhnnhchNKVTwfqZXGjzYN2jDcPBxytdsYnZ7WBcXCGcTadZycpOZpXOa00KJzEMAnP/D3fPN0XZ797n%2Be723tAd1Cq/r4e5a43c%2BNOznhIKAA4qePLEAAKshDChMEBs0v88%2BUztDTGuYgA5IlDESJ%2BL9mTv0/t/EIncALVkjrbFyM5Y7tlHgBQSw88qcRhtgC4cRCbT0zu9Ak4M1pMCoF4C2VJDZz29hXIBf1mZrw3qcLeEMqE0LoekfeWocKS0Pgg%2BubFxYBihA/Z%2BQUYEf0MPAm0XM2KQ1oJItw585ZT3IVrIQXhEi5GvFqBQXhaBhgYVwvRBiUhGOeKYsMQsQFNS4BobRqszha2MfYkuvwuFeLMfCDQ%2B9KH1F4Q4dIQ83YclcUZWJQk/F2ICVwYJPDaHhIEJEpqABaSesSFazwJG/Z4ssfHKnqDWeEkolCNAgFJNiCgHSVLLG4fxBBAmkB6vowx6BWnoj7CrBu5SaJNOqQQWp1V6mNMlByVp8I2idOsUoHpiSCB9PxhwBYtBOAAFZeB%2BA4FoUgqBOD7UsOPL0yxVgQiBDwUgBBNAbIWAAaxANsyQQoNAAA4zBmDiHELg2yvmfK4HqPU0gtkcEkLwFgEgNAaFIPsw5xyOC8AUCAeF9yDkbNIHAWAMBEAgCWAQRIbZyCUDQCSOg0RQgOk4KoT564snrkkBcYAyBaxSCFGYXg15CAkE7HofgggRBiHYFIGQghFAqHUFi0gug2ioWRIkTgPBNk7L2Q8o5nAC5thJWGVATl6WMuZay9lE93lmAuBADwlL6BuRuXMXgmKtALAgEgCliQqVkAoBAD1XqQDACkGYPgdAYFoogBETVERggNBhCq3g0bmAQQLhEbQ2pMW3IpTLIutA42yqwBELwwA3BiFoGi7gvAsAsEMMAcQ%2Ba8DYUcA2Z4mqpzajbGsW5wRmQQsObQPAERkQQQ8FgTVSI8AworaQZtxAIg2JuNWow/ajAPIWFQAw69nZPFQgXAU8aJXCFEOIcVQr5BKDUJq%2BV%2Bga0oGsNYfQA60WQAWHBGo5aslSSFqYM5lgzBIpnUWLAT7eztHTekFwDB3CeBaP4SD0x%2BhlCSCkNIAgxitCQ3kdI8GSgDAmFUMDAguijGg%2BMUD6TagjB6D/GYuHbCUbQ3oSYjRsOzC4AsC5KwxVqo4LshFmrkUXCNUyllbKOUWqtbgPl9rARsadauhYF44wDBAy8yQgIhRxEBGCjQkgzCSE3BobZ64EgQqhaQGFMmhTri4OuT5cRgXrjeQCzT64%2BOyuRai9FdzV04vxW6wlurSU%2Br9XamlbBOANBYA2PUWSmAMxrRPOIQouAfJ5fgYiAq2inpFce6Qp6pUXtlboYNiqmDKordx3jiLeDIp1cStsFwDWCYZcJ%2BLYN4jJY%2BVam1nq7XXMBGYR13msWuvdagW10QyW%2BvG71gYEojDxBcSGsx0Rw2RtlYm2N%2B7NvJtTem/dWaFI5rzYcgtRaS20DLfuqtNa62nYbWB5t5bDltp1Myfd3aqiav7YO2NI61iHPHZO25M651KAXbd3mPn11ME3du3djB93ZaPWKvLsgCsysOcV69K7v1WEsA%2BiIwGX2JDfZwD91Uv13t/f%2B6IgGW3PrIzUCDUGsjocCNRhDORkM1AY20XIKGGAsdo3YAjFHuh86Z50SjwvENMaaCR9D8vZcSHY0sTjqv9Dqrc0izgzXjUsvm3zDrKWgkQEk8RfrsnhsuoU0FLAMQQOmehSAQESWdN6m2XEUFgJdP6ckG0arWqUW2C8867FuKCVEr1VNkL1LaUcEiyalgCgGy1gbB160ww0tScywenLqOD0Y8va70gpXyuqq1zxjV7ntWBf1Ya5Pqf0%2BZ55MMbrM2vX9cBEN8Po2UCd7tbHwfAw08GPhBnuI8Is9tNUMy5bYbKDrcOTtvNtzV8prTQ4A743s0MFzZqs7xbS3ltuTdpdAPK0PfCU91tqh23vanZ93tvAftDphP9sdRZge8FB/OlkkOK6I2fAG6CgW6mAO6e6U6yOoqEgaOkq56mOOgpeBguO1ONgP2xORypO6Q5a6wdSeO1gf6NWAG8kWBou5GLOkuHORQXO/OPO6QkuAuNQKueGHQhG9GiujG%2BG5GRGVGtBOGcunBbOjGMunOghmuHGqwmuEKVW/Geuc%2BLKKeaeCcred4YY5u6WJAVuve8mpAimDulA3GZmMKvyQogIgI2ygKAecKFheotmOuNWnAnmGKehqm2yGmIKeocKnykg/yXA3yb4VegINeuuIefe3G3KjhwecmI2CwM6qQzgkgQAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/recur/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/recur.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/recur.test.hpp)
