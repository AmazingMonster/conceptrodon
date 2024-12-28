<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::ClassicTrek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-classic-trek">To Index</a></p>

## Description

`Roadrivore::ClassicTrek` accepts an operation.
Its first layer accepts another operation for composition.
Then, it returns two commitment functions and twelve continuation functions.

- **Commitment**
  - **Conjuration:** When invoked, this function instantiates the first operation with the arguments. Then, it invokes the second operation using `Omennivore::Send` with the type result of the instantiated first operation as the packed vessel.
  - **Transition:** When invoked by a vessel, this function transports the conjuration function to the vessel.

- **Continuation**

  When invoked by another operation, the function returns a `ClassicTrek`
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
   >::type
   >::type
       &vellip;
   >::type
   ></code></pre>

## Type Signature

```Haskell
-- Compose with Mold
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
ClassicTrek
 :: template<template<typename...> class...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
ClassicTrek'
 :: Commitment
 -> template<template<typename...> class...>

-- End in Transition
ClassicTrek'
 :: Commitment
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct ClassicTrek
{
    struct Commit
    {
        template<template<typename...> class...>
        alias Road = CONJURATION;

        template<template<template<template<typename...> class...> class...> class>
        alias Snow = TRANSITION;
    };

    template<template<typename...> class>
    alias Road = RECURSION;

    template<template<auto...> class>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RECURSION;
};
```

## Examples

We will see two examples that demonstrate conjuration and transition.

- In the first example, we will compose `oper_0<2>::Rail`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Capsules ****/
template<typename...>
struct Capsule;

template<typename...>
struct Capsule_1;

template<typename...>
struct Capsule_2;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        using type = Capsule<Containers<Shuttle<Variable>>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename...>
    struct Detail {};

    template
    <
        template<typename...> class Container,
        template<auto...> class Sequence,
        auto...I
    >
    struct Detail<Container<Sequence<I...>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I..., J...>>;
    };

    template<typename...Agreements>
    struct ProtoMold
    {
        using type = Carrier<Detail<Agreements>::template Page...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
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
using SupposedResult = Capsule<Capsule_1<Shuttle<10*2, '*'>>, Capsule_2<Shuttle<10*2, '*'>>>;

/**** Metafunction ****/
using Metafunction = ClassicTrek<Oper_0<2>::Road>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Road<Capsule_1, Capsule_2>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<Oper_0<2>::Road<Capsule_1, Capsule_2>::type>
        ::Road<Oper_1<10>::Mold>::type
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRoad`.

```C++
/**** InvokeRoad ****/
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule_1, Capsule_2>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Snow<InvokeRoad>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Road` and a `Rail` in the following way:

```C++
template<template<typename...> class...Args>
using Metafunction = Send<Road<Args...>>::template Hail<Rail>;
```

Note that in order to succeed, `Road<Args...>` must be a packed `Rail`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<auto...>`. This requirement is not checked by `ClassicTrek`.

We will implement `ClassicTrek` by performing recursion manually, meaning the function will recurse only once for every invocation of a member template.
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

- `Radio` is a `Road` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
struct ClassicTrek
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Road<Car>;

           // Helper function for the member template `Snow`.
           // This function transports the conjuration function `Road` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
               // We transfer the conjuration function `Road` to `RoadVessel`.
               using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Sail<Car>;

           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZpIA7KQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJSal2mA45QgRMxAR5Pn6Btpj2pQzNrQTlUbHxiSm2LW0dBd0K08Pho1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxutwImBYaQMUJMAGY3AQAJ7vZhsR7KJjIADWmHQADUfnZEdgIQtiF4HI8hK5HiZklZks9EVY7hCoTC4ZhEcjobCmPCkaj0axMAA6KVkx7IAwKX4eQRMZZkR6ixjiqUS7D0NiCBRkikEKk0ukMdB8pUtVV83XQxgEBTao0I8kcpkQx7e9UCnl8rmC4XItGatgut2y%2BW/ADy72IQpyRruPselOpBBemBttC9PoOB0eAEkGAA3VD4hkANg0cfiiYEJhrjwA7oQEOqEJhqxp7fqnS6axK897GRZHl4skZ1aGGQjno86wn%2Bna9Y7ndK3WyGSy2RCR77uULeSK/ceA6GMZLN9go0wFdrbsBiJgHQbk7dU5PwsBHgAlVAmHQOcF1eHM%2BSfF83wHG8QBADU9w9VkEXZcE7kDf1TyPYMMPPJEmC8IgI1vOV7w3YdI1IhVaSIPFiFQVAWFIQ8gxPNwCKIm87wfKU6QARy8T4fg/dMzVcPlmlQOiGJYCTMAEoTyNdd1wU9FMfVwnCzy07C2I41BiO4pTKOjRd4wbBgP1TUTMzAlVc3U70C2LMsK27Jta3MldmzbAgOz89ya34wSGD2JShwPMcJynX8NRAsz6xXJFgsU4jt0ZZDUIPTS2JygNtL0wiDK4qjjJI6NH2fV9%2B0NLdHOin9aXs%2BK7LoCCqugsq4IQlD913XqOUBEFhtBCEgSOYtuWgiy/lOMFxpGkEwTGwsPL/ICnA8x48F%2BJgewAoCPOHdCCvy3SztYi8xXDEqKtusj/w21ARJNDNHjcaM8GQAAVF9cT61DU3GrMaAif9AOA/4D2cjz2OILadsePaPIAWU8S0IvqvKsMukVLy1e7qLhqyfRsrF6KIA7LXqscD3zM53sYlhCH7WaTjBVNSdemkPBYZmCDp0c1M/TnOeBpVtB2Gaofq0XHhhmt1vwZ7m0MYDYdaLbWm7NAYUyAlHi7F9jpFuXvWx/lzrx67rwo8qyO1IQ8GAZhaFqlSzZ9b9pyp%2BLzUta2w27JXNuS53Xa6%2BDQzJbqCvBw6kWJrcBrQ02zecgAJXp40eKgvFC/pc5ITtuzYVZiBYnkeyEBhUBbI7BbFwtvoQRG84LnJ1QTBgFAyNpfgC2UBEl5dO/bxoBH2iGtt8hBtkzcJy1xRrCGYxugcLMRaDrxq87aI3HjSeiwt%2BGIUUeVAAor1vgCNgBaEgsAr8f%2BmddeNNOnHMMt3Gf%2B/jUryGVKkAu6dsjLxyJCSXoJNPZk1ag5NOctaay09vLQsAB1bsJpDAKCoPEEuQ8GAjxmi/Tua1p7NiIFPICxIFTQMxog1B3tYqzkRAuKmtDSRIipq6QGqCMqIVTqg%2BWDNfo4OyJPGWjDOYW1kZ/P%2BeEQw2xAQ7QmZUjKVSgjVGBZtmG0lri2Fq2Z7LtS0euYi3Vo4pyQf1LKKCRFPGtOELw0s5qN2ci3Nu%2BcJ4MCHnrJQA8uyEOIYXUhk9yGHVVhaAhHlILVXMdKBhctnKREvlghAQpHiYFLIwTs2xb49jiZ1QcGhtq/FLK0PAG1kDMUIBfBgtBz5bzrrtNMP56BI2IMAHwjoTbJObq3X4iM4iiEnIFO4HUaolNbHQWgjw4jRQNlQxebkewfTIl9X6mB/pIiODHEAygKaoB4TWUg7jCwtlbsgDsGTfgCEafU7saRWjiihBXDW8MkmizkVbJRQcVE8QlEU7RdVpF6N9mw96n0fp/StEzQgsddIQP2Tlcml9jnTyRMChJdtBHnMeJ434YTfG62KD8AhaAiFS1Cd4wuESMalLVjEms2KDQlL6aLBWEyzHvh8rM%2BZ3YxnAWWa5SssNoVbJ2W4PZbo4KHPRUIeyHKZHyJ%2Bb/fSAL1HAKlKyp0OivYxSanQeK6yFSbNhYneFBBEWsWRbK%2BCcd5VEEVW1LFkycW8MirY/cWNVWqvxjdMB2qgXuvfKCr8hqIXzjRZTTFbhdVlTxfVYGrxQbdhdXMqRG8CWDNzrSzuiNB5ZGZgYCug8PJOoxZE0pWA03ASYDEVAOTlVoOLJmDJFp6CBJ1vebslz4jjOJs2RGyNFYmK%2BebP1vyLYarUZq96mtw1c1NJmStGavV8LFgzXm/NWZZtFmTHdhBG7IOkUDbdw9qWd33Z7NV/8A22xlMGp2LsxDu3ft6cFEM/biUDleR6ysJLhzfRYqO7wUVx3XYnRd5IU4fsroou9iH/XKLnWhoNpkOFQNzEu2B3NbLGLavY1Mp7hEGsanFSFWG6E4bcDw5Om6zYCLg8R%2BmTwxE9wkb4m9ZskM6V/rIh9mrhPoYTfq0Weia51yMeBN1PKYJ20seB6xotmN2OkeLWQzjXHs0bnx3KQnROhr1bhiNjUo0LlNVkGF2y4V8wRQ6pF9HsA2qrpW%2Bj8bjOJpY9I/TF1v6zow6ooLgKxOmfI9ODNJqJUWrcEe61jnbXOdc8eGNqAoOefk95xjamfVpz81/RRgWn2gJK8FsLHsIu/ii5CtdJi5PxLZTePF3rBr3EWiNeaDMABieBiALEeNgVQrBYTdikQtDro02vmAROEOUXgsBzjcJSvYaQTMqTGgzIQCBCIEA6VImdRU0p3DJtt3b9Ak3tccUwNICgvBdrZlcTkKH/nNZO/hhdt37snnU4J1DuL3srs%2B3d%2BgAB9Lgl2/uvYB7cQ9N2QeYFB2YS74tWjEG%2BBXA7U71VHfQy9IHcN0fxBRwzJcoPSlY9%2BfpR4hJKkNou6CsmZONAAwZL66dL3AHoetCqCI/WdFk3c9PGmwtdGGso9G9iX2GdxdkLz%2BItU3BnYIHttitP0f05PLB7AaUVNC0ynl1MBW/lc5C%2BRCrB4v1AXikLhOmXGsKc9UhEnTwydcEe2CQ7VCUb3ccLCDH%2BO3pu4BtlTnBMYfWQ%2B/AnczIDdtaN6dGmSJ15Q9N2VomcvVRnOI174qZvaTyRCnsbPZ7AtFkiqZuBhHaM89tMlQvQk%2BRFl19rjden5GBYAFLiYatObEwB3KS8z3zuSClQpsR97QP3tAMdHGb1KZineW%2BCJI61oRH9p2GZDVlgXH3K1o1oNTNOpG5Z6Il5ZtHAekTwNMQ792KWoRYiYAP3XOW1%2Bh83/9i39U9EH/VtG/fdGW/YpZrODd/IaV3eMJHD3Z7KnIqGnOnGIBnFSJnKA5HD0RjY3YrEyYLFKcfd9eqKvcCEXRjMzacc/YHb7UfIvYSJEdXKpJArXV/L1OPdfSdDnOAziM3TRO/HRcFZqSFG/BrEAxTMDH7PqVgzbJ4IQLwNIMldAP8H4X3GAu4STWQ%2BQxQkHTMSFKXBHK0eHb7cHCSHbFXGXLgDQI4MwZiMADgI4Gw5SZiXQww5HZKEw1XPkcwyw6w2w%2Bw5OVvHzYGFGYxYlFQ24X/YI/NcJSXGLWzJEZnPkFwlzEAZzCEOCDzYPJEcw/ZP/D8OCDLMnFwtwGwuwjgfZdaV1FSOCeLF3E4f8JQqfUI8Feo7Q6NIIloYlNIuNJwsHLgRwgwsHRImoiab6H4J0UIhYRMZAUHMieIAgCABYdAOCBQcUaYxXTQ33ZiGQuQ/WBQ5oskdYFHAZbsfgWgbeNsacDyCYxwKYmYtoLaBQOeFsX4R4ghVALyHIXaF8PxeQkAY0SY1YpQNoeYggRYkAZYtgVYvkA8f2CvNwdeGEuIqAlnJERIzou3boxHXoyggYlFKxSrUWNEgONwDItwLI%2B1HI%2B1BCJPfEx4PI%2BrYktAvkYo3wpI8onDGkkvVMLYjQvYjkN0A4gIybYaLraQhoAQYCIbEbfbNxCAoUy4ZaWUiaEsJeTAX2SnATbHe9f7dPLVTDCGW4LpQPGkZUtyKmG/DAy3cXVhaNKmA04AfQ6XTEvox0pHJ3VSSQk6DgjUz/aHHUkTIFLpAgsIw1E0/ECzFyFUs06vCCQM0DHqdTYGdYhoqRJorQ8HeKNopgDokAKTeuJEUM1UzFWDBM0RUY8Yloa4gE2Y4E0E8ExHe8PkJMggcHTY9QnYps/YtkDgTYWgTgfwXgPwDgLQUgVATgOEywawNMbYXYdyMwBEHgUga1Ic7szYXEAISQCUDQAADjMDMAAE49yuB/BtytyuBkhkhpBeyOBJBeAWAJANANBSBBzhzRyOBeAFAQBHylytBNg4BYAYBEAQB540hCJyBKBSU6B4hIhxROBVAtyqw74qxJBHhgBkBkBHgpAJQzBeACRCASA8BFjej%2BBBARAxB2ApAZBBBFAVB1BlzSBdBeiWwEw0hOAeAey%2ByBzNBeBXyYxCIQLMxUAqBHg4KEKkKUK0KMKNyzBHgIBeY0hIL3k5yuB1heBvzuzSAIAkAIL6AyAKAIBtLxhgApArCaAp8FdKAYguLSAYhwhWgURWLeAbLmBiAUQYwYhtAGglyFzdZ%2BwYwGl7K6KsAYgvBgB2JTiPzuBeAsAWBDBgBxBAq%2BtPK8AckIrhzMBVAGhCJ9gFzwgoQrzhyZ8YgEwXKPAsArKTQ8A7zIrSAcliBG0lBXgYqjAZ8jAuLNgqADBgAFBCRvgWw6xByFziLhBRBxAKKhrqK1ArKGL9BYqUBrBrB9A8AYgPzIBNg3jX5OA74Fi2FTAJzLAzAXzar0csAVqIBNh6gfEXALRZg/BejQhlhKhqg9BiguMbrnrMguMRhHrxheiLr%2BhBgZhPBOg9A/qmhFgvqxgEhfrFg3roahgIby4JBzrpy9gkb9AOKnyrLXzhL4LELkLUL0LMLpKIBcA8LFL5yVLFy2rNguwgJxgzrSA1zJAEQJQ9yEQLyNBJAkgawNB/Aqw9z0brzbyQB5yJQqwuAqwty9zTyqx/BJAjy2aqxMa6LXz3zPyqblzfyALNKgK%2BLQK9KDLiBoK2BOBWgWBSxkg749pSJpwuA9yJQuBNycL8AiBjq9AhrSLRrpBxqlBJq6LdArCmKbsHL2KOB%2BzlaXzOBeKCB%2BKL4hKRK8a7xbb7bHbSlZLGJ5KdKGQ5yzBKa1LfytKM6FKwL9Ki6dKUADAjA7bzC%2BA6A3kPyIBLK6KnK7KHLrLbKXK3KPKHA26fLHQ/LGkrKgqQqwq3Y27orYr4rhz8AXxGgUqrL0rMqoQ27cregrLCriqURSr9hhyKqqqFzar6rMBGrJ6fw2q%2BBOrurer%2Bq26PaRryLvbZAJraLhyA6ZrWrdqrBLBFrlr4A1q1sPjNrtr5xP7rADruKjqCKfg/6eg%2Bgcgrr3AgaCg7qLQEanreiXr%2BhYb0gPr%2Bg0GfrYGkqBAAb2gkHbrCGfESH8GoapghhsGJi2hqG0aFAUbyLQ7w7nzuLOAcbRLkKbbfw7aHbNyZLSbXbs6KbVLqbSBaan5KBQ6bzSA7yER7bObkh/A9zzyEQubJAkLejOGRzOA1avzz6/zALgL9bwKy6oKYKOAzaxKWAFBSx0LSxBGeQFhnayaCL3bZBPaH7KL5BfaX6dARbSAg6WLIr2HOKVao69aBL477HHHnHXHjwBt06YQFLxGEQ86THC70mdKS7DaQAnG5DQcXG9zQc3HmzVAkLa6zL%2BsLKrKW6XK26mnXL3LPLe6mZ%2B7/Kh7MBgrQqt4IqFyJ7mqd6orEq57oG6LF7kAsqV7BA166KN67Lt7yr0d97eBD79YT7mqz7NaL7n8r7MA%2Br0Rb6fH76JBH6qLAmpqQnK7jB5rv7CrTr/6NrDgFi5q9qLBwGRzIGTqYHQbnAIBXBsH7qKhIb3qSgchsHMGcgmHfregiGBgYayGQbEXKHwaHqIW4bAb8hyGGGlhwXEblKtgdhUaSWryOGsbuHqnkKHGnHHgymJRKmRGXbi4ZtlLJHNaabMA6aEgGaryFG7z9yJQEQERAhObzCNAxXkhJaI6uG3zbB1b87VyQBJB/BWazzkgHytzJBDyuAdyzAlaryEQonI7FWVXBbsL5WDGLWpHaqshnBJAgA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/classic_trek/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/roadrivore/classic_trek.hpp)
- [Unit test](../../../../tests/unit/metafunctions/roadrivore/classic_trek.test.hpp)
