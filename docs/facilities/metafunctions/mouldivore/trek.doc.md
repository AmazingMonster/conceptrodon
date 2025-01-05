<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Trek`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-trek">To Index</a></p>

## Description

`Mouldivore::Trek` accepts an operation.
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
 :: template<typename...> class...
 -> template<typename...> class...
 -> ...
 -> Commitment

-- Compose with Page
Trek
 :: template<typename...> class...
 -> template<auto...> class...
 -> ...
 -> Commitment

-- Compose with Road
Trek
 :: template<typename...> class...
 -> template<template<typename...> class...> class...
 -> ...
 -> Commitment

-- Compose with Rail
Trek
 :: template<typename...> class...
 -> template<template<auto...> class...> class...
 -> ...
 -> Commitment

-- Compose with Flow
Trek
 :: template<typename...> class...
 -> template<template<template<typename...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Sail
Trek
 :: template<typename...> class...
 -> template<template<template<auto...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Snow
Trek
 :: template<typename...> class...
 -> template<template<template<template<typename...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Hail
Trek
 :: template<typename...> class...
 -> template<template<template<template<auto...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Cool
Trek
 :: template<typename...> class...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Calm
Trek
 :: template<typename...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Grit
Trek
 :: template<typename...> class...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment

-- Compose with Will
Trek
 :: template<typename...> class...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
 -> ...
 -> Commitment
```

```Haskell
-- End in Conjuration
Trek'
 :: Commitment
 -> template<typename...>

-- End in Transition
Trek'
 :: Commitment
 -> template<template<template<typename...> class...> class...>
```

## Structure

```C++
template<template<typename...> class>
struct Trek
{
    struct Commit
    {
        template<typename...>
        alias Mold = CONJURATION;

        template<template<template<typename...> class...> class>
        alias Flow = TRANSITION;
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

- In the first example, we will compose `oper_0<Shuttle>::Road`, `oper_1<10>::Mold`, and `oper_2<'*'>::Rail`.

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
    template<typename...Vay>
    struct Detail
    {
        using type = Capsule<Sequence<Vay::value>...>;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
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
using Metafunction = Trek<Oper_0<Shuttle>::Mold>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send
        <
            Oper_0<Shuttle>::Mold
            <
                std::integral_constant<int, 2>,
                std::integral_constant<int, 3>
            >
        >
        ::Road<Oper_1<10>::Mold>
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);
```

- In the second example, we will transport the conjuration function to `InvokeRail`.

```C++
/**** InvokeMold ****/
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Flow<InvokeMold>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will compose functions using `Omennivore::Send`.
For example, we can compose a `Mold` and a `Road` in the following way:

```C++
template<auto...Args>
using Metafunction = Send<Mold<Args...>>::template Flow<Road>;
```

Note that in order to succeed, `Mold<Args...>` must be a packed `Road`, meaning it is of the form `Vessel<Items...>` where `Items...` all have signature `template<typename...>`. This requirement is not checked by `Trek`.

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

- `Radio` is a `Mold` and
- `Car` is a `Mold` or `Rail`.

Here is the entire implementation.

```C++
// `Radio` is a `Mold`.
template<template<typename...> class Radio>
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
           template<typename...Signals>
           using Mold = Send<Radio<Signals...>>::template Road<Car>;
           template<template<template<typename...> class...> class MoldVessel>

           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           struct Detail
           {
               // We transfer the conjuration function `Mold` to `MoldVessel`.
               using type = MoldVessel<Mold>;
           };
           
           /**** Transition ****/
           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
        };

       /**** Continuation ****/
       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           template<typename...Signals>
           using Mold = Send<Radio<Signals...>>::template Sail<Car>;

           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
              using type = MoldVessel<Mold>;
           };

           /**** Transition ****/
           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Mold>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQgZpJBAA6oCoRODB7evgGp6ZkCYRHRLHEJSUF2mA5ZQgRMxAQ5Pn6Btpj2jgINTQQlUbHxicm2jc2teR0KEwPhQ%2BUjVQCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulyuBEwLBSBnBJgAzG4CABPF7MNh3ZRMZAAa0w6AAap87HDsKDZsQvA47kJXHcTAB2Kx0h5wqzXUHgyHQzBwhEQqFMGHwpEo1iYAB0EuJd2QBgUXw8giYCzId2FjFFErF2HobEECmJpII5Mp1IY6B5Csayp52ohjAICk1BthJLZDNBd09qr5XJ5HP5goRyPVbCdLulsq%2BAHkXsQBVkDdcvXcyRSCI9MFbaB6vbtdncAJIMABuqBxtIAbBoY/F4wITFW7gB3QgIVUITCVjS23UOp1VsU5z30ix3LwZIyq4O02EPO41uM9Bg2nX2x2Sl0s2lMlmgofezkC7lCn1Hv3B1HijfYCNMOWaq7AYiYO16xNXZPj8LAO4AJVQTDoDOc5PFmPKPs%2Br59teIAgGqu5usysKsiC1z%2Br6J6HoG6FnvCTBeEQYY3jKd7roO4YkXKVJENixCoKgLCkAeAbHm4%2BGEdet73hK1IAI5eG8nzvqmJquDyDSoLR9EsOJmD8YJZHOq6ILukmXo4dhp6aVhrHsagRFcYpFGRvOsZ1sum5qZ6InpqBSrZlZdx5oWJZlp2DbVmZS4ec2rbtu5VZ8QJDDbIpA77iOY4Tj%2BarAaZtbefCQUKURW70khKH7hprHZX6Wm6QR%2BmcZRRnEZGD5Pi%2Bvb6pZH5el%2Bk5CPZcV2XQ4GVVBpWwfByF7juvVsn8gLDUCoL/PshaclB5nfEcwLjSNgLAmN%2BYeb%2BgFOD5eBfEwXYALKeOa4VofleU6eeIqhsVJnrfgqDCUaaZ3AAKs%2BWJ9ShybjRmNARH%2BAFAT8%2B7OR5bHEFtO37YdHmDo5uWYSxF0hle5FlaRdxg%2B%2ByY2eidFEP%2BgERapdXJk5xwYwxLCEL2s2HMCpPWY9lIeCwVMEPuyYjhzDPfQq2ibDNQOOQzTmrVWt2bY2hhAaDTQ%2BU0nZoJC6S4ncHbPrDJMi8xGFBpdKNCHgwDMLQNXKdr9XRXcB20DLs5UmJ8IS/dSVGybpXEt1%2BX/YT8KY5uA1ayL8O8udCO62ql4GSV0cmTb%2BKEl077c6TzkABJdLGdxUF4IVLtnJD%2BXcbBLMQOtHl2ABitCoE2MMp19%2BbPQg23Z7ndQCKqcYMAoaTNF8BAdtKAj84uWRt3n48efHPktoPGzpuEpZYt%2BdyEExDe5vmYg1y2k45806t3CkdGhV8MSIncqCD/EatG%2BrAC0JBYGXOeTwIjqb4zxq2Zm9lf9uT6FtU75gAOqdiNIYBQVBb432HgwUeM034dwYFDW2PkiBoITnKJOx0g7AIajFaccI5zxwJDg7M8IZ4ByARbdKCF8GkwAd9V6UCiioKFow5MIceGnSFBeDU11SKx2ERKCCVU1xYwIVbautcWp/zavCcRnUiLdWDAw7W9DA4p15rIcIXhBZzR0U3FuXxkH5yVmkJQA8h5oAQQLfO5ip5VhnlLM0RcPLKOqv2DQmsRbOUiNfCBCABR3EwMWRg7YNjADbJ4jq3jJSNlbsWJoeANrICYoQK%2BDBaCXx3rXSG0V6B3CaMAHw9o/E8xMa3VucRRDjgCtceJa4fG%2BVoLQO4cQoqq0wUvNyXZXqYHevCfYnsQDKDxqgAmR0NCkGMc2FuyA2whK%2BAIXJ2TOwpCaKKcEZdZbgzwcHPhodEb8P1iI7iYovGSNqiLQhPs7ZzkGcMtwLM2Zex0tbaGLoPksVxtfKZAN2qQQSajBh8zm6tycZ3SxKsbGKxHg48e0LUHT2hm4oCcC4kgpaYk3x8zsUSLfI2Fs7TOmdgaZi1Aa9XLlg8s8nkoyfnjMmU1OglTSa8LDic3WekLmlUMhVHFb5bkM3uWyjpJCXpvQtJTQgvyuRfPQcy7K/yiASuBUS6CYLA6c36plOGxyeECKuqjQVYjmkivNpbVe0y4oTIBdMzVKjrzgsct9J4v1OwStpucYG1SzHt3zq3OBGQqYGDLliqsDr8ZAsbFgL1QEmAxFQBEjlotCzphCWaeg8LpR3k7E2dWjTMZJMhmtf%2Bhz1JGprdyvlQjLlShKhjOWorv5PRjagDVjkubC09Lo1m1N7S%2BvpgzHGbzCAp17Vw3M5M%2BZIs7pw4B5dsImoNm7MQZsAH3PjnFU05onYbRdm4Q2xtN2pRVd7DVftW0km0X2zltbTk8twnrZG/L%2BVKuwUSNt2scatQcjO4cxNl02snLFKVZDE6ULcNQu9tDNH6r3A%2Br65NWE93YSOgBXLn3GvOQ2gVMcLXCodFIi29zZFNnkWBJRlrtVjJ6ghr0WiDWMN0YIfRhi6YpxwxHNdH7iNaq3Q%2B%2B5dqpUMr9nKggCqK5wZk%2BCNVgLfZuGuXqC9rGjnct46%2B%2BtZqiN6fKoJzqZHPxWx9eJmVknB3Sbgt7OTtnPmduvSpujHtdXMaQ4NLW2ntLPt002wzBnRFXNcyZ8VzUpVOf/rRkjbnMqedQjcRaI15rk0rngYgsw7jYFUKwKEnZOELWS6NLz5hYThBlF4LAM43B2O2CkUjtUxrkyEAgAiBBimcJDv52qONWvtfoG6pL9w2IpAUF4TrRiTpaf4666446mBjYm8eVjvMmjEA%2BGXLrT7eWFQE2C%2BbTN0xgw2/EIb30FwAH0NBYem7h45PW0ZUWSiFY8ykcZXY0B9WkhqZv4bFHiJgiITP/oUYBvVTGwNEJeHFUb43BtJTksFbYPJAeIlgik7wb31NEwysh7zRrZshdi2Fq2u6pUAedaChj6jtEJea/cK7XBbtgge4Va2E3HBQk2w9H%2B8ViCXa4B9LKhP/sg6OxmLMgCWP4%2B4TtnTe2CMO3kq9piumCzi755TxHKuUfwgLBe61wHIcroKhxMUAApEzUP0RMGAO5e2L29ewc53gbn8R9gG4lExC3OOe309%2B7honqnGtG6iqvcn9sTs8/hNrlzJPL2ObtyjZ08W8deYu7GS7ZgWfdfZ4DjbyaEfvYl1dswwvA8RzZ%2BbgLwWndCV/aDsC/uTfh/A8QqPi34esXrzVNwBe0kxGL37rWMuvNy609XoqQXLkh%2BE1rUTEX7Zx7n6ouCtO0/nZa14FIVjcS/k%2BJzln4qd97/QAf%2BH6YpVw%2BW%2BJNrBAOusS4BofYZgmJgA4PsD/xImL9YfwjtwZ/fYWEd/T/b/AOeDfHb6PaP%2BFFY/MnWAoNKee2CTNwT7O/AbN7WCODUEWCJ1eEJnHkZ/MZHA64WCZzMvHkD/L/DgMZdaRRZSWCCddme9YbQ4P8Q/WgdMThUTTgq/e2GAxoFFbA6GNkeEfcWYdAWCcIcEJ8MQS7OxWYQwFgtwGQpicvF0OZRySQ6QwQTAOQ2gBQj%2BRoQQHkNQu4WEZOGhKAtDT4B0FnJQxwZAS7UieIAgCAHQkABQUUFwvvC/TnX/U/FWc/Pg4kFYc7ExTsfgdpWuVeDyRwvAZw1w5oHyBQBAApNWOROBVALyLIHaZ8YeZWJQKQw0eMJInBZoDwggKQrwnwu8HkfcfdCKcQlDJolDBolDZMdApKe/R/Eg0QoDYcFowY0mTwmQ/QuMQwxQkwlQ8wjQ7ALQkY7Gao3Q2QyYownuGYswwQJiSw39TRfY5jQ4z0PAoFAgrPIXeEYg5lUg0fX9cg6LNArPDQtwag8A7APA6LMPRY5MIQII4o/wrgvcF0cI1gorYrQrFrWoAQICHLPLSbbjIaCEgEZaJE9gosZeTAXdbbSfP7d9JXeOK4YgYAXnJ6DEtyeOSnN0BDe5CDAQw6IkkkntYYv9FYkAcYgwjYpQ0w%2BEOYn/BuMYvQzk6Y5Q7YggXYkzVPPqdPRLHzHKInWvWfYk%2Bfe5cknESPOcNUrEw6FfZUtfRjGw%2B4QE7gqbK4Xgy/QXOKQQpgYQkASjHkLUnAsE2wrLThBI8opQSozw7wtgXwnkY0wXQI3fYI40sIlkDgNYWgTgfwXgPwDgLQUgVATgNwawawFMDYLYdyMwWEHgUgaTeMiMtYLEAISQMUDQAADjMDMAAE5qyuB/AKzyyuA6Q6RpAoyOBJBeAWAJANBZk4yEykyOBeAFAQBZl8ytA1g4BYAYBEAQAF4UgCJyBKBLE6B4hIhRROBVByyKwH4KxJA7hgBkBkA7gpAxQzBeBcRCASA8ApCuAZBBARAxB2ApB7z5AlA1BNAdA9Amw4wUhOAeBIzozYzPzEzOAowCIFz0xUAqA7gtydy9yDyjyTzSyc8IAWYUhVy9lsyuAVheBxyIzSAIAkAVz6AyAKAIASKRhgApA38aAuD4gRyIAYgQKYhwgmh0duBeBWLmBiBEQowYhtBah8zcylZewowckOKEysAYgvBgA2J2kRzOLSAsAWBDBgBxACzlKMshK8AIlFKEzMBVBagCIdhczxj2yEzaA8AYg4xeKPAsAQKjQ8BuylKIliAU0lAnhVKjArKjBPy1gqADBgAFA8QPgmwaw4zcz%2BAHzRBxAXzoq3yVB1BNLdA7yDA/LTBLBrB9BrKRzIA1gcilxFKH5JCSFMqrBLAzABy3KNssA8qIA1gagUEXAzQpg/A7zQgFgygKg9ArF2E2rerCglxBhuqRg7ymqlw%2BhJhPA2g9AJr6g5gRrhgEhxq5gBrVr%2BglrS4JBGqMztgdr9AgLSB%2BzeBBzYLtzdz9zDzjzTzULcArysKczcK8z/K1gOxAIRgGrSBizJBYQxRqzYRWyNBJAkgqwNB/AKxqzDqOyuyQAcyxQKwuAKxyzqymyKx/BJB6yAaKxjqQLBzhzRyXqCzJyZyiK5yILFzyLKLiB1y2BOAmgWBiw6QH5doSJJwuBqyxQuAyyLz8AiBaq9AErHy4rpAErFAkqQLdA38fzFt/yCL2yYzcbNLBzwKCBIKr4YK4LLrbx2bObuabs0KGIMLSLaRsyzBnr8LJziKjbMKlyKKbbSKUB0rqK6zZk6LdlGLmLNLuL2K5bSAfbeL%2BLBKHA/bRL7RxLckQLpLZL5LTY/aVK1KNKpLtK6g9KQLDLjLwQ/bzKQKrKbL2L7KdgEynKXLcy3KPLMAvLE7vx/K%2BAgqQqwqIq/ahbYrnzRbZBxaPyUrEh9A1KUBUzLAcqYh6qCqGs8jOASrqiyqB6LAqrTqaqbzPh4BGqugdLnAIBXB1rggzQtqeq7y%2Bqlwt6D6shd6xrOhugFr%2Bgt75rehFqurlq5q1qZq8gNrmhT6VrdrNh9qcLobFaTrQKOBzr4L9y2afwOauayy7gIB7r%2BbTanq8LXrSB3qX5KBAKYbSBuzYRObga6R/BqyWzYQQbJA9y7z/78bbBCbLbCLSakB5zKblyHa1yNyOAGaEKWAFBixjzixwGuRZheaHqbzBbZBha27XzO7kqEzdAQCZa/zOK0G/68awKKaoLNa2GOGuGeGjwstDbIRMK4HYQLba6ybqa7bqaQBOHd9LtuHqzLteGCBLtVA9y%2BA6APbKAvaEyA6OLczPGg6hLQ7KZw6JKo7MAZK5Kd5FLcyE6fKi7eB8BnxU6l7NKM7kATLs69CLLeA87bLERC7HKNtS7eBy6VYq6fKa7ia667cG7MBwqURm7hHW6JB27BBxHJa4be6MqZ6h6R7Eyx6P5OBdgdDyrrA57EyF66rl7z616/AN7Wrn72rt70B37BqMhD65nln2ElnxrV6UEpqWg1mtmL7b7Nr77trX69nch5mlC36Tm97P7MyDqFbgLlbOBYK1HOG7hrGxQ7GoGYHC4yscKEHia3rMAPqEgvr2zOyMHEhObYRYRAhgbn8NBYW6RkalaBzOACaxzEGfr/B/rmy6RezyzJA6yuBKyzAcb2zYQnn0WhyiaJy0Hzy0XTqMW6XCzSA3KMhnBJAgA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/trek/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/trek.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/trek.test.hpp)
