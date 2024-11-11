<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Sink`

## Description

`Raillivore::Sink` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

In contrast to `Skip` and `Skid,` `Sink` introduces a new scope to avoid name collision. Hence, it uses the name `Rail` for both initiation and recursion.
<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Sink ::   template<template<auto...> class...> class... 
       -> typename...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> auto...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Sink ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class...>
struct Sink
{
    struct Realm
    {
        template<template<auto...> class...>
        alias Rail = INITIATION;
    };

    template<typename...>
    alias Mold = RECURSION;

    template<auto...>
    alias Page = RECURSION;

    template<template<typename...> class...>
    alias Road = RECURSION;

    template<template<auto...> class...>
    alias Rail = RECURSION;

    template<template<template<typename...> class...> class...>
    alias Flow = RECURSION;

    template<template<template<auto...> class...> class...>
    alias Sail = RECURSION;

    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RECURSION;

    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RECURSION;

    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Lull = RECURSION;

    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RECURSION;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RECURSION;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RECURSION;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RECURSION;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RECURSION;
};
```

## Examples

We will move the *0*th layer of `Operation` to the end of its invocation order.

```C++
template<template<auto...> class...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

using SupposedResult = Operation<std::index_sequence>
::Mold<void>
::Page<0>;

template<typename...Args>
using Metafunction = Sink<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::Realm::Rail<std::index_sequence>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Sink` relies on a helper function called `LoadSink` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.
We will implement a simplified version that only handles `Mold` and `Page` as a demonstration.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<template<auto...> class...> class Operation, typename...Items>
struct LoadSink
{
    template<typename...Elements>
// User inputs will be kept in `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSink`, waiting for more inputs.
    using Mold = LoadSink<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSink<Operation, Items..., Shuttle<Variables...>>;

    struct Realm
    {
        template<template<auto...> class...Sequences>
// When finally initiating the operation, we invoke the sinkped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
        using Rail = Press<Operation<Sequences...>>::template Mold<Items...>;
    };

};

template<template<template<auto...> class...> class Operation>
struct Sink: public LoadSink<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxCAA7GakAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxickKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHASYLCkGeyYAzG4EAJ4pjKyYANQA8tfETHUMp9gmGgCC48ReDjuymImAUCi%2B3xMCSsPzucLuewOR0wp3OVxubAAdNiPhD4Xc/gCCHcACKYRp0O5QqwJEmnGGQn4AeiZdwsTCUd1EShAELx8MRh1eKNh8NR/PxcMFyNRl2uzCxOJO2C5BjBdw8giYCzIEJZdwAKgg4vc8Ao7gJaBcLeE7ikmrc9sQ7UxkABrO70KgETESyVyjGYbGYzV7QTg0Vw3GRgkEf6AskU2io0Pa8LEFOyRgEBTB3HKv3UvWsgDqpoYADdUG77gRjVySCCFGkGPgjAj9kK9nc2EtnagqAj66hnq8ssW7gB3QgIIf3TCqOOuvboF3u30x/FeDLtgNUk4kx6jt4gEDS4V3ACynnQmcE2dzSs%2BJwsVJjULpL75MfPx3fZz9fFfxRM4mC8Ig82VVUOXNIRMAARy8RhtlIQD4TAiDsVDB9CwLGNCQTcltWTM44MQ5CQLcbDw0g59PnfaE7m3MJgARdF90PJ44jHZwz07ZEgSYYBKOonNaPpKlaXpb9vn1AAlbpNgyCt7m5dgZKA/jhVwtw0KlLTjjOAMFSDJ9oPVVMdVQ5lS3uJR7Rebs63uGhiHGF0XjYJ01w9KhiFQFg5wtZy3I3b5JQFdETODUSFGs8KIrY%2BVbmDB4QojBKozwzLY3jYlE2Iu8KXTIqH1o0hHnS8SGIZRKmJ3Vi91OQ9gVBDK6vFGy7jLO4wirGsgrQYgmxbNtGoM%2B5ewqC1B2ci1j3HLrpzrIKFyXBxMFXe11wnI1GAqyd7ntdU5qbLxaGJaJXQ9IggSbc1%2BGdKhNhC3rK1QUQ3lzPT/Si24j24k8%2BKRC9r1oW8zli6qcvxaNZNZOQGG3TafPNJp7hBZALmQehV0eu5nuaY1nT6j6eIYb7N3hU9gNJIi6FRNLicfX1lRp9FpIYz8GT9YCdJ%2BvnQPA1BaPM2CEKQhgUJ%2BjCRawrNw3iurjJS7EmbidqxWy/ECPy%2BmSLcMjJe2UqaKfCr1dCp9C2hH7mN3djmrutrZT%2BtgAccrIaYmwThNNsTre1xLvZB7sCoZs5LZZj52euTmco/ePYZ/CbXeSxVMW%2BYAQX2HCg7he3WLB1cnfDg2s5ztgzdZ7BY5AnmpK/H4IUFtF09MmuIV1jUmBSBRzvrmTW9l6Hu6EBBwIIeh44nHrp1oWh6vuEx/A0ABJRFwVXhFUDuGtMBSBEXndGal5JhgUnAynvlb2/U6FzCa7F0WcZgj3yYqlWM43/ZwWy7vgioCYOgIQYQ3R8ltinUOlEv4d2wPQKuOY4b6kUHEN6l8cxTjoIvWIe8D7EjCFSVebhe792ntvQwW0DDbFXK8VarZT4r3XpvX0q9drGgYAdI6b85prVcCjJhP8WBbw0HcK6J9bpMMAcA0BDBwGrwOtqRw7Z8YsBIOWDB18twNSvDeDidxpEgLAYzBaAgKpCJZhVEhfcB6ongbnau%2BZnw8ygV2SiI9sQADUmh4CYNEegf96I5ULr7ZeB4DFAKMXIkxgMsjmJYdiCq49J7TzON44gvj/GgnEgWJujIcrdwUmIFgNtaqJTvtA1EHin6vzBMGI2FFAmzw4QTMIYgrRvUyGOXcw5TGcKnOWfqtZ6w7jdNcVcBgLhxDCvqPa/TDouhOvWMI4xDCOGFKuEcsSBB3EoWfdBV8Jy3QeFXBgeAqwglPK1dU%2BNCavVJp9LIWjEohLksRfR1y/5uC4p7AQqIGlS2yYHWuwM3G6PBqiCxOSylRkbi4yEcKh733OMi4ewsX5qmjlBWp5ofnkzhmPMBIA7ReH8XgZAESZHGMjn0j4kkaTcxkkyAAVKytl7KmR6jZQabAQgDRss5cydlwrmWCvyeYE4YQcZeCwPuNw4E6CEAuHDFuqLkXVLpTi0ecYiTvzeBA18vNUVuw7nDHWOrATAlQEQYupSBbqvRdbKmcJu5WqIMoISy9baIubs6jslSH5y0ztnTADikH50lCEj1wkPn%2BXdZ61EFdQ2IKxc4m2jLfU5Vvia4MSaw1NJjCE4usbrWoFtWcPNKboUQIzfkkJQgvApDSEodACkyHEidni/VZxxjoFPGELAqgAD6ShyKArhqectbgqx4AhkEq5CazgaHzPC7N7dc3EGAAW74RaiLPSlm8fRsjwE0u2e8NmIAp3fE3ammePxXmgnOh28Jl491eAPeOM4M650Lr9kumOIAim0BYKeN5Ec3C9v7a2BcI6JYURXTJVZjhkBDpgnEAgEBIMgAULcVDXy21PqSY25tm0CMXQ%2BCsekHA1i0E4AAVl4H4bgvBUCcF0pYawBINhbGXmYE4PBSAEE0NRtYboQB0ckJiDQkguAJBOBoOjGgzD%2BH8GYAAHGp/QnBJC8BA1wDQGhSBMa0KQVjHBeAKBAIZoTHAtBrDgLAGAiAQAbAIBg8glA0AHDoHECItxOCqDU/4AAtP4SQdxgDIApVITEZheCbUICQWdeh%2BCCBEGIdgUgZCCFQWoYTpBdBcFIJOF4KROA8Bo/Rxj%2BWzMPHAhg0%2BgWQthYi1Fu4MWzB3AgB4bz9BnQSq4CsXgNm7OkAgEgLzKQfNkAoBASb02QDACkMkGgF0NaUGiPl6IbTiAXHK7wbbzBdsPGiNoboNmBNecQQ8BgVp8tYGiF4YAJCF6WeY6QLALBDDAHELZ3g%2BBMaOBUm9kzC5FJ7H2%2BQe8tG/v6DwNEF4u2PBYHy3GPAIH3sqWINEdImAyRfaMLQFiwm1hUAMFuzxeBMCTi4kxgTqXhCiHEFlhnuX1Cw8K/ob7KBrDWDh9ESzkA1gji%2BpwYLvbmqmA45YMwJnUBY4yVgQXEA1hdB6M4CArgpjtCCK2QYZQKh6GbUUbIng2hG8KG8fXwx4hFbV28PokwzfTGqLUXocxrd9j0Ksp3uQdc%2B/mKUG3EhVfce2CHrTHAGNGZq5wO4TXQvhci9FyTnWIC4ES/1vjg3hsk7WMaYBIwVekDE5IE4mIACcJwEiSGk2YSQq8FP%2BAr5HnTpAQP8cxP4DoamK9qY6BJrgdGq%2BBGMyxzgFmrOCZJ2Npz42XP1fAh5ubAUpt9b82wTgTQWAVgSMFpg0F2xcAr5iLgUn4v4CIIrlLsh0vM%2BkKzpQeWOcgGSCV3u%2B3KtR%2Bq7D2ri/iQDi7LEA7574H6vxH4n5n6iLdar7TZUh8ZmBDbT5/b2YTawF9bL7zZ9YgDb677BbgFLYV76Z8B0BOiWYQCbaw6HZNB7bvbUHHanbnaQ5XbZg3Z3aw4PZPYva0BvYCafbfa/YmYA7nbnKgj5Zg7IDgQ7ACZhB7Aw4mZE4I40HI47AmZo4Y4CZY445KD44CHE4oF8Dk4KCU7U606Q4M536ZYP6yBs75a6DJAGBGA87S42CKHK7C4pCi4cDi4EAQwkhS5WAy5y4K6zpiFC6u4iEa5a7O464hALAG4jBFbG5vDa4W4ZBW7xHB5241CREMCO4tAxHe45Hq55Ee6ZFe525zCpGVH9Ce6G6DbrCbDh4NEw7R5j6mZx64GgGH6sTH6n5SZdYZ5X7wH8ZIEjYiakAF5YDxDF4w5t4d4n7SYJDD4JByaSD15hZFbtFmaT7WYz4ObOaubuazZYG%2Bb%2BYcDb4tbCIVgUoVh9HIjjAX6Z7JZFYWFM5WHZbyBP7s4ma6AnDFalaf6R5tGx4cB1ZubgSnyXHhbXG3H3HCjuQwG9ZoISonBjH7FoHIkzaeboEjA3FNpDp3EV5DoPEECobAFhYkFrZuQbZbY7a0ECb0EXAnZnYODMEBTXa3a0FCGYCPbPbtK8H/b7ACGqH/Z4CA6iEg7xaqDg7SG8CyE1D5aKGI4XAqGo4ZIaG8BaG466GE76GjZk5CTGFU407yjmG37vESDWE5bfF2EgD/GOHGC86WD87uGmaeFPKcBMiQYBHWCy4sYhFK7wCq7FEnia6tjVG67oB1GJEFDpFZCRnJFZAxm24RElH5GRn27u61HlH1GzD9CZllFB4VGh5NGZZf4gm/6dEUkwkKA3F3BEmYikmDGX4kAjE57IF2b56YCF4zFf7zGv4n4nAnB0aKYyYGbDkJD%2BCabbET62BT7jErCiYgCSB0aV50ZqbKYV6SAV5ybV5cAOmcAnA/5y5zmLlf5xYx5VnmadkTFY4ZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/sink.hpp)
- [unit test](../../../../tests/unit/raillivore/sink.test.hpp)
