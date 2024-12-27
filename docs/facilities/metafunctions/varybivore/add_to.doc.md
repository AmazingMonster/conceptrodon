<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AddTo`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-add-to">To Index</a></p>

## Description

`Varybivore::AddTo` accepts a variable and returns a function. When invoked, the function sums up the variable and the arguments.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub> + V<sub>1</sub> + ... + V<sub>n</sub> + Target</code></pre>

## Type Signature

```Haskell
AddTo
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AddTo
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will add `1, 2` to `3`.

```C++
/**** Metafunction ****/
template<auto...Variables>
using Metafunction = AddTo<3>::Page<Variables...>;

/**** Test ****/
static_assert(Metafunction<1, 2>::value == 6);
```

## Implementation

We will implement `AddTo` using a fold expression.

We will place the initiator on the right side of the expression to conform to other similar functions in the library.
This means we are doing a right-fold.

<pre><code>   Variables + ... + Init
-> Variable<sub>0</sub> + (... + (Variable<sub>Last-1</sub> + (Variable<sub>Last</sub> + Init))...)
</code></pre>

In our case, left-fold and right-fold produce the same result since `+` is commutative.

Here's the entire implementation:

```C++
template<auto Init>
struct AddTo
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Variables+...+Init)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v 
    {(Variables+...+Init)}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzLGkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMsTcTC8RCuDEIIOwvyGxC8DnOx3Q6AAKqhfiYAOxWE7nQnnf6Ax6YEFgiGoAB0tIAavU8EwIvQFLDfkTzgikQRzspiKgiMomMByQSibiLOcOZyiRNHMhzmgGENMKpEsRzuDIQA3MReTDS8Wy6V4iAM4hMlmYNmWWnU6yXaEEWa4gAiIKlMsJ7s92ONxIBtzJFO1NNpx2AxEwAMYBDZsThAa8qSMfJFhpBbr5AqFGYpkejscECnt7Ni%2BJ%2BAZJweBoLD9otVtZ7ID8rwiuVqvVmrD6dFAH0dUbjpzJebGcyW3baY7na6cR6KyPfRX/adPh9vu8NudsKpWLdDS9fjvNwd1zvzgBZTB1KheBgOdLPC8nGtA8n1qmNyfWhNJscKbBMAN53kwD5Pk8WYomimIUrEsIgCAwqihSTZTjaZaJn6Jynjs5zojavInic7bIAOTAKEoDQQLe96Ps%2BAgUq05xmEhIB6t4maxEu2YAGyumuJwcPMtCcAArLwfgcFopCoJwbjWNYXKLMsmZmLEPCkAQmiifMADWIASZI1IaAAHGYZgAJzWVwEkWeZXA4ji0jiRwki8CwEgaBopAyXJCkcLwCggH5umyaJpBwLAMCICAiwEIkELkJQaA3HQ0ShKwqyqOZ/EALT8ZI5zAMgipSNSZi8Jg%2BBEJa6B6PwggiGI7BSDIgiKCo6iRaQuitAA7sQTCJJwPBiZJ0l6fJnAAPIQslvKoFQ5x5YVxWleV5yVWY5wQB4GX0Jq5habMvARVo8wQEg6WJJlZAUBAd0PSAwBSGYfB0P8xChRAEQzREwT1AAnuNvBA8wxAg3NETaJgDjg6Q6X3AQc0MLQYN9VgEReMAYK0LQoXcLwWAsIYwDiNjeDRs%2BOo2jNaoIxCqzacE/zuXJtB4BEI3Qx4WAzQQlreSTpD08QEQpJgboAhT3NGHp8xUAYwAKHSeCYINc2JIwSPNcIojiB1BvdWoM0DfoFMoMplj6DzoWQPMqCJNUxMFUM6BZqYljWGYgUSw1DNO20CPVC4DDuJ4zT%2BJHUx9DErS5GkAijC0SQpCnDDxyU/TjJUYcdMMjTR2ModMTUxc5zM4zF2negTA01d5/MChqSsEiTRwUn%2BTNQVrflRUlWVFWmXtEC4IQJDSppXDnTpSvzAgmBMFgMQQIZICSLE1LWbErkaJIZiSPxvkSfx1n6JwnmkN5WnUvxXD8eZ1lOfxJn2Xv/G931QUhWFC9IrXTijdBKi0UpPResdbKbBOD1BYDqHEBUmBKgMGmLg1lqRcDMjVOqJA8CNVaAbVqxtpCmyUObPquhPrDVGuDLuPcAq8CCgtJKEJzgrQHhtEqyA0GgQwVgsy%2B1Dr3WOjPWIZh56XSiqAqB0RUrPVQEdfovCKYYK4H5GgtAfp/QBn1SGoMkYGOhrDeGiMxYozjOjTGM0cZ4wJkTJGZN5arDkvgWmjh6bEzkkzZALMkbs0qDNbmvNQYC1cRdEWSMJZSyULLcmRgFagCAXwVW6tNba11jJbSxCjbtTIbIM2vU5LUKtorH2Vg7YhMdhveSrt0ju09t7W2Fh/bMMDgQ4OtS7CF2cBAVw9dWiBGCL0XOicM55HSIMiZWdm7jJ6RXToIxS7pwWdUJZ3QRnTDzrYOuKyG5Vy2QnTuCwlgdznlfbu01f6cC4UPVBFMdqYOwRofak96riLnhdRepBl6r36LU9yN876YMPjiCS1kXKxCPifSQrQmGzWCrYAB0jgHwFAYlJaCi5HEBgaseBm0WAKB1IqHUAjPxDFwVPBqTVZAkPyZ1eQFDik6DiKQWhY0SYMOuYFea4DlqrVUIS4lpLyVkiGMIpRojojiNiFIpW0VbpSoeti5Vx1OLIESIkIcGCBwUoIAOIVZDvrRF0YDYG0MjEWphnDMOSNLGCGsVjNxmBcb4zEI4sWzjEkRNIO4wuXjGaqGZv8AJgggl9RCXzEG4ShZRLFjE6W8T5YgQVSrEU6StY6z1mLXJbUJAFK6syi2bK%2BE219lUh28Bnb1IEMTNYnty2VNaQHaIQcamtwLhXCOUcsjp2GUUY5SdM7VGmcnaocyG5dvWXsvtU72gCA2ZO2uXRpmN02YOsZJy25nPatyn%2BvKOBrWFSS84ZLMH6reXgk6s95VAKXivNelAu7ApADZak8QJIOThb5eIOJn4HuYZwf%2B4UflGUkBJXezkcS%2BXMpIOyXBLJmG/u5WIPKgNItRV3aqgHEXfPveLU16Qt5AA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/add_to.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/add_to.test.hpp)
