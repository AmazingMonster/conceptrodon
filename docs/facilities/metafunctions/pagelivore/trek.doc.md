<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Trek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-trek">To Index</a></p>

## Description

`Pagelivore::Trek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `Trek`
  - that is instantiated by the conjuration function and
  - whose first layer is instantiated by the new operation.

In general, this function composes operations together in a similar fashion to `.` in Haskell.

<pre><code>   Oper<sub>0</sub>
-> Oper<sub>1</sub>
       &vellip;
-> Oper<sub>n-1</sub>
-> Oper<sub>n</sub>
-> Args...
-> Oper<sub>n</sub>&lt;
   (unpack)Oper<sub>n-1</sub>&lt;
       &vellip;
   (unpack)Oper<sub>1</sub>&lt;
   (unpack)Oper<sub>0</sub>&lt;
       Args...
   >
   >
       &vellip;
   >
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
Trek
 :: template<auto...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trek
 :: template<auto...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trek
 :: template<auto...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trek
 :: template<auto...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trek
 :: template<auto...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trek
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trek
 :: template<auto...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trek
 :: template<auto...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trek
 :: template<auto...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trek
 :: template<auto...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trek
 :: template<auto...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trek
 :: template<auto...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trek'
 :: Commitment
 -> template<auto...>

-- End in Transition
Trek'
 :: Commitment
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class>
struct Trek
{
    struct Commit
    {
        template<auto...>
        alias Page = CONJURATION;

        template<template<template<auto...> class...> class>
        alias Sail = TRANSITION;
    };

// Compose with Mold
    template<template<typename...> class>
    alias Road = RECURSION;

// Compose with Page
    template<template<auto...> class>
    alias Rail = RECURSION;

// Compose with Road
    template<template<template<typename...> class...> class>
    alias Flow = RECURSION;

// Compose with Rail
    template<template<template<auto...> class...> class>
    alias Sail = RECURSION;

// Compose with Flow
    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RECURSION;

// Compose with Sail
    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RECURSION;

// Compose with Snow
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RECURSION;

// Compose with Hail
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RECURSION;

// Compose with Cool
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RECURSION;

// Compose with Calm
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RECURSION;

// Compose with Grit
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RECURSION;

// Compose with Will
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RECURSION;
};
```

## Examples

We will see two examples that demonstrate conjuration and transition.

- In the first example, we will compose `oper_0<Shuttle>::Rail`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
template<template<auto...> class Sequence>
struct Oper_0
{ 
    template<auto...Variable>
    struct Detail
    {
        using type = Capsule<Sequence<Variable>...>;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename...>
    struct Detail {};

    template<template<auto...> class Sequence, auto...I>
    struct Detail<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
    };

    template<typename...Agreements>
    using Mold = Carrier<Detail<Agreements>::template Page...>;
};

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

/**** Metafunction ****/
using Metafunction = Trek<Oper_0<Shuttle>::Page>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Page<2, 3>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<Oper_0<Shuttle>::Page<2, 3>>
        ::Road<Oper_1<10>::Mold>
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokePage ****/
template<template<auto...> class PageArg>
struct InvokePageDetail
{
    using type = PageArg<2, 3>;
};

template<template<auto...> class...Args>
using InvokePage = InvokePageDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Sail<InvokePage>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Page` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<Page<Args...>>::template Flow<Road>;
```

Note that in order to succeed, `Page<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `Trek`.

We will implement `Trek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
We will showcase a simplified version that handles `Mold` and `Rail`.

We will use a simplified version of `Send` to compose operations.

```C++
template<typename PackedVessel>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Send<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Sequences...`.
    { using type = Operation<Sequences...>; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};
```

Note that in the following code,

- `Radio` is a `Page` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Page`.
template<template<auto...> class Radio>
struct Trek
{
    /**** Define Road ****/
    // `Car` is a `Mold`.
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           // `Radio` and `Car` are composed here.
           template<auto...Signals>
           using Page = Send<Radio<Signals...>>::template Road<Car>;

           // Helper function for the member template `Sail`.
           // This function transports the conjuration function `Page` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
               // We transfer the conjuration function `Page` to `PageVessel`.
               using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Page` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Page>::template ProtoSail<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    /**** Define Sail ****/
    // This function is the similar the `ProtoRoad` defined above.
    // It handles the case where `Car` is a `Rail`.
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           template<auto...Signals>
           using Page = Send<Radio<Signals...>>::template Sail<Car>;

           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
              using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Page>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZgDMXKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJyal2mA45QgRMxAR5Pn6Btpj2pQzNrQTlUbHxiSm2LW0dBd0K08Pho1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu9zOjyErj%2BpzBBEwLDSBkRJiSbgIAE93sw2I9lExkABrTDoABqPzs6OwEIWxC8DmhsJMAHYrKznuirHcIYjkajMOjMUiUUw0RjsbjWJgAHTymmPZAGBS/DyCJjLMiPKWMGXy2XYehsQQKGl0ggMpkwhjoYXqlpa4VGpGMAgKA3mpK03nsiGPAM60WC4X8sUSzE4vVsT3epUq34AeXexHFOXNd0Dj3pjIIL0wjto/sDBwOjwAkgwAG6oUmPEwANg0yfiaYEjY0jwA7oQEDqEJh602XSb3Z6m7LiwG2RZHl4skYdVH60lno8W6n%2Bs7jW6PQrvdz65zuRCp0GBeKhZLg5fQ1G8XL99h40xVQbbsBiJhXaaM7cs/O4TAI8ABKqBMOgK5rq8hbCh%2BX4/mOT4gCAuonr6XJJDy4J3GGIbXheEZ4beGJMF4RCxs%2Byqvnuk5xtRqrQkQJLEKgqAsKQ57hlebhkRRT4vm%2B8owgAjl4nw/H%2BObWq4wrNKgLFsSwcmYGJEm0V6Prgn6maBsRRE3gZhE8XxqCUYJGn0Qm64pm2DB/lm0l5jBmpFrpAalhW1a1oOHYbnZHbdr2/a%2BU2oniQwewaROZ4znOC7AbqUE2a2W4YuF6mUYebKYdhZ76TxBWhoZJnkWZAkMZZVEJu%2Bn7fqOZoHu58VAdCrnJS5dBwXViFVShaFYaex6DbygIguNoIQkCRwVgKiF2XCJxgtNE0gmCU1lh2IEQU4gV4L8TBDhohLAEKMW4SVxXGcKpnmZVoE7agUmWrmjwACpfsSQ3YVm035jQESgeBkH/GenkdrxxB7QdR0ALKeHa53/npl0Edxd7SjGFXWZDDmBk5BKsUQYEQbFOnI1mjx/R4LAsIQo6LVcZ74y9TI03TBDM9O5OU7z1MCNoOwLaDzW81Tm1Ntt%2BBPU2jyGJBEOtIFrSDmgyKZGSjwDl%2Bk6i7zRWkWVBpCHgwDMLQjVaWLAEJQSTCnclNp2hiUu7elpvm1VNL9SVQOkxiuMHiNOEU9bnkABK9CmjxUF4kX9DHJAhY8bCrMQXGCkdQiuR2uuh2LnlvQg%2B0x3HjQCDqqYMAoGRtL8BADkqAtCwnsfxzkR0nWdnY9g32x5uENbEq1hCcVzlOeWItCoD2i6x202uPGkrFRb8MRYo8qAN/EWum9rAC0JBYOnbfl9XefWyj11o/hIrX7xRvYzRd3WV3lKqr0eOXwTnVufnvMznHmHMsAB1QclpDAKCoDvbeTcGCC03B3U%2BCcOxd0CkQTu9tMDv2pEjS%2BvNAKLiSuiNcb8qSfwxGgoOP18E5XQiHfBVMoQfUgdkCuIt/6UwNnfdGN8SIP34nRaqz8n5CVlPBequ4v7W0IcBbOdAOoFhzhiCRvVKL9SjPQsWdDg7j35oIcIXhhbwj0WWIuJdkEdzVsUH4yc0DwJbkgsuKCmxoNlvLZOHZVENXHBoC%2BfMyyRC3uAhA4pHiYCrIwfs2xgB9i8T1HxCpZYlyrK0PAO1kCcUIJvBgtAN5TxnjDBK9A5bEGAD4N0/iJ5mOLr8EucRRDzlCncBJu5fFBVoLQR4cR4qawwYPHyR0PqYC%2BhiI43sQDKCJqgEmiMNCkFMd2YuyA%2ByhN%2BAIPJOTBxpFaDKRE6dFZQzwfrVGPDb66gfC/ER4jWm/iapw2RfsFarnep9e07EOY%2B2MnbU6EyCqEy3jM4G3UEKJKEfQxZ5jfiWIrtYjW9dG72IQQtGFDBMG/PcbaTxTZvFtKSX4xZ8TQVSNlj2Tp3TBxNMgv07ydYOzDNGW4cZ3oUJTMBfI2gVSszcJ5ac26oiqoWVqsSu5VsCG2w5clBl7zaaEC%2BdxH5V5sDyszmyogHKQWSNNFlYOWYdF5Wary%2B%2BFz9QCuFVq900jHmzOSmqoF/s3C4u1U%2BCFzU/qvABoOSVHDfo1Isc4juJdYFZDpgYdOsDUHTNmYFLAnrIJMBiKgSJXLPLljzKE209AEWq1fIOLs2tmm42STDLaOdjkBiNbws5/D%2BVCKFQKx4gcxUBgJnajVzVAF6yYU8dm9M3SMzBGLAmvbOZds7Zw36UJ1TIoTj6/B3Da0mzNmIS2QDAyPK7o7WSLtHpyQ9iunVyrUK%2Bw1QHJW1DTxdu5acytt9a2KkqlcxiZCP5FnuYwn%2BSiupXsDOOxh67bbEJeS%2B6klCsFehoZffVl6J0lmYVXEoHc52X1vfwhdj862PrNfKJ1lr334MeZKkh%2BZYIqNuUhIRGj3haIAcNA1nD9GOAYEY2dJiu2oaIveU1mGao4fI6urt1rgZSreQHD5crj3fKoUe/5dro1kZFRRiDMGxYccKnyjDD7eM8eubhgTDyJXtWI9KsTsqCAqsvIqv5vs23KMdfxnVkGjy5RU1fKtambqaastcrTun%2BNWsMwo4jtmuoKYtV7XRdGYMrVWhcZaUIABieBiALEeNgVQrAUSDg4TF2LHDTzJHCMqLwWAVxuHsXsNIeGtJTShEIBA5ECAlI4ehwRz0rR5nq41%2BgrrIQ9qYGkBQXhmtsduDyrjWNwV3GHQNobPXdFjX68QYg3x04tZvRptr3mxHtdepDFb8Ret/Q3AAfU7Ot41m3yo6cYhlSKSqLQdZSsQM7316yGquwackaSE3zebdmVmzkv1/z1TzMWjygNrl4oN4bPE7t7GFN9lbv2lWObJi50aodWvXb0wF1qm7iO/01Wo5CqFNGRYxyHY7KYTtcAHXyK7jxYbDccCiVbu2mSna4N9fKN6JuPim6HT9hYjwckp7zy79973bd%2BPDzAnFa3lmkcLuzcvhTlkPWTJzbm70YYAFLSIA/jrBW61L3eFMz2grPaCraOBr%2BUnE9do47VFzH17jX8/Nb1PHi54a0GeVD1oB2oYYiJ2F73LLJMKq7s77S4vFsnGeydsw9OLpS7Ko8JH6SYh/ce69U7Zgecfcl1W6XwixFy/045QHJGc4u%2B10bohy5iPQ7m3D1SEUoqI5%2Bzn1HLrdW/tdwwnXaHPvYZuYpqvjfgLbSCy8sP9nJ/qLJ9RinR26teDSDY9AIEfgs9T7cQjm/t%2B77m3mFvs3YdyQawQJrPEuAaCOGYTiYAOBHFfzSTiXXb/zbcA/o4SQL%2Bb%2BH%2BQctIC2fWiesMSiqKB%2BjyUBLQMBxmombgp2Gg1%2B3WSqrK4G9yKE8mKBNO3OGID%2BEyfuzsWkKEp6%2BB8Qyewor%2B7%2BHAEys%2Bb65BIAI66%2BTwp%2B%2B%2BHC1qe%2BVuyU8BTAqKWBvyGIz%2BjwSQymmOf0b0Pw7oB%2BCwaYyAJ2NE8QBAEACw6AKECgMoyhjUbgnBVuX%2Bx%2BGsO%2BvBnM3o6wR2NSg4/AnSM8rUHYChjgShKhbQgUCgCAhSWsM8ycqAtk/QB0X4Tc6sSgmhFoihuhSgbQ6hBAmhIA2hbAuhwoZ4TssUGIQCqRGIqB6BP%2BmBky2BbgYhEhoBQCuBwKWRBBwoxBkepB0i0iFBdmBetBwBDBkeTB0iCyzUQgxhoRBho64IFh7BeWwI8WTwMI9ikE6WmWI2S0tWwxIx0WUIlYQ8KgJuF27mY%2BN2vwXctwZSHOeYyxPkXcROvoTmEOzewGWCuxwAwoRRkhcevWHmhsW25etE1x%2BmjyhxpIBOLyXxqxp0C%2B7xy%2BA09Gf0fRsBtsfRtO/B0BAazgIAlBfx0mQxM0MhqWHCTheALhH80RGhWhOhr4woUJqQ0IPRZIfRNIlhWEHAmwtAnA/gvAfgHAWgpAqAnAbg1g1g2Y2wuwvktQvA5mzJNJmwxIAQkgsoGgAAHGYGYAAJyylcD%2BBSmSlcCsisjSB0kcCSC8AsASAaDzJMkslskcC8AKAgDzKClaCbBwCwAwCIAgD9xpDkTkCUDWJ0DxCRAyicCqCSkNj7wNiSCPDADIDICPBSCyhmC8BkiEAkB4CaGpD8CCAiBiDsBSAyCCCKAqDqBCmkC6CpBdiphpCcA8C0n0mMmaC8DGmJjkROl5ioBUCPA%2Bl%2BkBlBkhlhnikp4QA0xpDukHIbACkVnWlIBun0BkAUAQAjnjDABSDP40BW7xBmkQAxAVmkAxDhCtBYjFm8BrnMDEBYiJgxDaANCCk8CkBqyjiJi5Kbk5lYAxBeDAC8SdJmncC8BYAsCGDADiA3nJbHl4CRLPksmYCqANDkT7CnnhCIiaksk24xCph7keBYArmWh4C6kvmkCRLECJpKCvDvlGA25GCDl8AGDAAKDkjfBdgthMmnmJnCCiDiBpk0WZlqArl5n6AfkoCcmWD6B4AxBmmQCbB%2BEBGcD7waEkKmCWDWBmBGkYUrZYB8UQCbD1BnwuC2izB%2BCpChDLCVDVB6DFBsK5CeCdC6WZD6UjDaXjB1C9C/kCCDAzCGUFCWV9BNCLBmVjAJB1CLBqV6AKFtCuVpwSCKU8l7ABX6BlmkCGmVmcCNm%2Bn%2BmBnBmhnhmdm4Axl9kpDrADlCnrCbADgQTjAKWkCimSBJCyiylJDqkaCSBmCSBNgaD%2BANiymhVak6kgApCygNhcANiSmykqkNj%2BCSCKmlUNjhUrnGmmnmmkCWk0mkA2n2mOnOnjmTnECelsCcCtAsBVisj7yHTUSLhcCymyhcASlRn4BECyV6A0XJn0XSCMVKDMU5m6DP4FkDZbmlkcAMnDU5lVk1nkSbwNlNmxUvi7X7WHWdhdnsQ9mjn1jJBmDpUTWEUQDDng29kukTlI2jkoAGBGB7UP58B0D7KLnLk5k7kblbmrnrl7kHlHkOCk3nluiXl5Irm3n3mPkWyk1vkflfksn4BfiND/krlAUgWIik0QW9ArkwVwVYgIX7AsnIWoWnkYVYWYA4Uc1ASEVUDEWkXkWUWk0XV0WpnXWyBMXZkskPVsUEXiVWBcUwXyUCVVY5DPkiWxFiWcUWBSWVkyVxk/DwCKVWXKUQCuBeUaW2h%2BU6WpB6X9CB3pAmX9Ah0WU9BOU2WeX2XqXx3WUDAuVaVuXeVJ35Ap0%2BVLAVBZ1cCBU7DBXF2NXvURWslRX/Utk7XAR7UHUSmPAQDJWnVQ1pUZVWnZWYC5UJD5WanamkC6lJD7UVWsj%2BCylqlJCVXVX9UfVGmcBjUWnw12kI0OnfUEAo2LXLX7BrUtksAKBVihlViN2CgLDHUpVxnnWyCXX63pnyC3XG06AtWkBPVFkvmvWV0jWcDVkEC1m/WNkH1H0n1n2XipZg3Ii9kd1JCw2TVDkoBo3xDb1IMJDH1b4nan2yknbn0EAnaqABm43zkpaUCE0snE17mk0UP7mHnHk00fJ01XmM2YB3kPlTzPmnns14XS2vk/m81e05kC3ICgXC2CCi05ni0blS1IUrZy28AK0azK14Wq2ZVEX2ya2YAUW4g623160SAG0ZlP0sWv2Y3GAu3cW8Xe2sl20CDPkHB4kW2SXSXxCyVe38Wp1%2B0B3J16CaWF3%2BVh3R05CR3h05Cx3uUeP9C2XtDeOOVp1RNhPZ1DCR350JPl0KBBWplf3lmfU13APH2PBYOyi4Mt1t1JzmCd1w2ZU9192UCvVD26lymyhJBJCBAVUP4aDNOsidUL2RUmm2DjXwMikgCSD%2BAlWqmsj6mSmSAKlcDSlmBDWalJDZOL19ODONWRk9PV2rODmbAYVZDOCSBAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/trek/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/trek.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/trek.test.hpp)
