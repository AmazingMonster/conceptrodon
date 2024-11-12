<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Skip`

## Description

`Raillivore::Skip` accepts an operation and sinks its *0*th layer to the bottom of the invocation order.

The only difference between `Skip` and `Skid` is that `Skip` uses `R_il` for initiation and `Rail` for recursion, while `Skid` uses `Rail` for initiation and `R_il` for recursion.

<pre><code>   Operation{FirstLayer{...LastLayer}}
-> FirstLayer{...LastLayer{Operation}}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Skip ::   template<template<auto...> class...> class... 
       -> typename...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> auto...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<typename...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<auto...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<typename...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<auto...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<typename...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<auto...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
       
Skip ::   template<template<auto...> class...> class... 
       -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
       -> ...
       -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Skip
{
    template<template<auto...> class...>
    alias R_il = INITIATION;

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
using Metafunction = Skip<Operation>::Mold<Args...>;

using Result = Metafunction<void>::Page<0>::R_il<std::index_sequence>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `Skip` relies on a helper function called `LoadSkip` to keep a record of user inputs.
The record will be passed to `Omennivore::Press` to invoke the previously provided operation.
We will implement a simplified version that only handles `Mold` and `Page` as a demonstration.

```C++
template<typename...>
struct Capsule;

template<auto...>
struct Shuttle;

// We will use `Items` to keep track of user inputs.
template<template<template<auto...> class...> class Operation, typename...Items>
struct LoadSkip
{
    template<typename...Elements>
// User inputs will be kept in `Capsule` and placed at the end of `Items.`
// Then, we pass the extended `Items` back to `LoadSkip`, waiting for more inputs.
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    template<template<auto...> class...Sequences>
// When finally initiating the operation, we invoke the skipped layer.
// Then, we pass the instantiated operation and user inputs
// to Omennivore::Press for further invocations.
    using R_il = Press<Operation<Sequences...>>::template Mold<Items...>;
};

template<template<template<auto...> class...> class Operation>
struct Skip: public LoadSkip<Operation> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgBykrgAyeAyYAHI%2BAEaYxBIaGqQADqgKhE4MHt6%2BASlpGQKh4VEssfFcibaY9o4CQgRMxATZPn5cgXaYDpkNTQTFkTFxCUkKjc2tuR22EwNhQ2UjlRoAlLaoXsTI7BwEmCzJBvsmAMxuBACeyYysmADUAPI3xEx1DGfYJhoAguPEXgc92UxEwCgU3x%2BJgA7FZfvcEfd9odjpgzhdrrc2AA6XGfSGI%2B7/QEEe4AEUwjTo9xhVmhZLOcKhvwA9Cz7hYmEp7qIlCBIQTEcijm80fDEejBYSEcLUeirjdmDi8adsDyDOD7h5BEwFmRIWz7gAVBBxB54BT3AS0S5W8L3ZJNO77YgOpjIADW93oVAI2Kl0oVWMwuOx2v2ggh4oR%2BOjRIIAKBFKptHR4d14WIadkjAIClD%2BNVAdpBvZAHVzQwAG6oD0PAimnkkUEKVIMfBGJEHEX7e5sJau1BUJGN1AvN6ZUv3ADuhAQI4emFUCfd%2B3Qbs9/rjhK86U7QZppzJT3H7xAIFlovuAFlPOhs4Jc/mVV9ThYaXGYQy3wK45eTp%2B5wBoS/5oucTBeEQBaquqXKWkImAAI5eIwOykMBiIQVBuLhk%2BxZFnGxJJpSuqpucCHIahYFuLhkbQa%2BXyfrC9y7mEwBIpih7Hs8cQTs4F7dqiwJMMA1G0Xm9GMjS9KMr%2BPyGgASt0WzpFWDy8uwckgYJor4W4GEyjpJznEGSohi%2BsGaumeroay5YPEojqvL2DYPDQxDjG6rxsC6G5elQxCoCwC5Wq5Hlbj80pCpiZmhuJCi2ZFUUcYqdyho8YVRklMYEdl8aJqSyakQ%2BVKZiVT70aQTyZZJTFMslLF7uxB5nMeIJgllDWSnZ9wVvcYQ1nWIVoMQLZth2zVGQ8/blFaw6uVap6Tj1s4NiFS4rg4mDro6m5TiajBVdODyOpqC0tl4tCktE7pekQwItpa/CulQWxhf11aoKI7z5gZgYxXcJ68WeAkolet60Pe5zxbVeWErG8nsnIDC7ttfmWk0DygsglzIPQ67Pfcr3NKaroDV9fEML926IueoHkiRdDohlpPPv6qp05islMd%2BTIBqBel/QL4GQag9GWfBSEoQwaF/VhYs4TmkaJQ1plpbiLNxJ1Eq5YSRGFYzZFuBR0s7OVdEvlVmvhS%2Bxawn9rH7pxrUPR18oA2wQPOZkdNTcJonmxJtu68lvtg72RVM%2Bc1ts58nM3NzeVfon8N/lN7upcq2I/MAoIHHhIcIo77EQ%2BuLuR0bOd52wFvs9g8dgXzMk/r8kLCximfmXXkL61qTDJAol2N3J7fy7DvdCAgkEEPQidTn1s60LQjUPCYABsGgAJLIhCG9Iqg9x1pgyRIq8npzSvZMMMkkHUz87cP%2BnIvYXXEvi3jcFe5TVVq1n28HBCXKvdgioCYOgIQHo8DJAFPbNO4dqK/y7tgegNc8wI0NIoOIH0b55hnHQZesRD7H1JGEGkG83D90HrPPehgdoGB2OuN4612wX3XlvHe/oN77VNAwI6J1P4LQ2q4NGbD/4sF3hoe4N1z73TYSAsBECoFsKOrqRwnZCYsBIJWHBd8dxNRvHeLi9x5HgMgdA6OS0BBVTEWzKqFCB5D3RMg/OtdCyvj5nAns1Ex64gAGpNDwEwaI9BAGMTysXf2q8jzGNAaYpRFjgaZGsRw3EVVJ7T1nucfxxBAnBLBJJIsLdmR5UfvA9EPjX4f3BKGE2VFQnzx4UTMIYgbQfQyBOfco5LG8JnJWQa9ZGwKDMTcdcBhLhxAioaA6PTjpujOo2MI4xDCOFFOuMciSBD3FoZfbBt8pz3UeDXBgeAaygnPO1TUhNibvXJt9TIujEQRIUgAfWpC7C5gC3A8W9gIdEtSZb5ODvXUGXiDGQ3RDYgpTdeYjyfhcOFo9Rbvw1LHGCVTLTfMpgjCeZiQAOi8MEvAyAYkKLMczbpnxpJ0hha3VkAAqBljKmUsgNIyo02AhBGkZSy%2BlTK%2BU8uKeYU4YQ8ZeCwIeNwkE6CEEuAjNuCK4UVMpei8eCYSRf3eDA98/MEUey7gjPWaqgQglQEQUudt6rJURS/A1yVe4mqIMoESq97bNw8XDIUiqkW4irpgFxaDC7SgiU60SRiHWoBDdRX1/rUXuLtjS4p2kykmT1aGaNqD6lxgiaXMNgUzV3nROmiqwdoVz1%2BBEoQXhkipCUOgJSVDSQu0xZq844x0DnjCFgVQzylCUQBQjc85rzg1jwFDMJ5znXog0IWd1D9U0%2BuIMATNPxs0kVejLd4RjFHmK%2BRSjmIAh1uB%2BIu2NZaV36PrZdRt0Trxrq8Buycw7UCjrjiASNU7X0vKjm4NtHb2xLh7VLKiM65JLMcMgZ5cE4gEAgL%2BkACg7iQc%2BZeq6aSq01u2ihggnxViMg4OsWgnAACsvA/DcF4KgTg%2BlLDWCJJsbYq8zCnB4KQAgmh8PrA9CAIjkhsQaEkFwaEpwNBEY0GYNea8zD%2BECIRjgkheAsFGKQMjWhSCUY4LwBQIAkhsY4FodYcBYAwEQCATYBAcHkEoGgQ4dA4gRDuJwVQ/g14AFo16SHuMAZAxKpDYjMLwbahASCjr0PwQQIgxDsCkDIQQmC1DsdILoLgpBpyvGSJwHgBHiOkYS%2Bpx4kEcEXyc659znnvP3F82Ye4EAPA2foK6IVXBVi8F0/p0gEAkDWeSLZsgFAIBdZ6yAYAUgzB8DoC6LTEBogJeiM04glwMu8Fm8webjxojaG6Lplj1nUGPAYDaBLWBoheGABQpeWnyOkCwCwQwwBxB6d4PgbGjg1IXdU0uZS%2BxFvkEfLJ1TtA8DRFePNjwWAEsJjwIpy7aliDRDSJgCkN2jAA6MOx9YVADBLt8XgTA04eJkZY2F4QohxDRaJ3F9QD3Et6AMKj0wNHLD6EB1pyA6wxw/U4C5ttrV6dWEsGYVTqAYc5KwCziA6wug9GcBAVwUx2hBHbIMUo5Q9A1sKFkTwbRVcFHeEr4YFRqi1F6HMOXehJfvD6M0PXA4zcm819MWY/Rrcq6axsLYOwJBZY4CR5TuXOD3GK25jzXmfO8aqxAXAQWGtMaay1tH6xTRgJGOL0gXHJCnGxAATlONCSQ/GzCSA3iJtemf9CcHk6QRTzHsRry4Gvfwmf/B1541wIj2e16%2B6p%2BpzT2nWNo/a8ZjrpmCuQUs/1oK3X6v2bYJwJoLAqzQhc0wWCnYuCZ%2BxFwPjAX8BEBF6F2QEXSfSHJ0oeLVPdCjdS/3RbXufcqYo5wfL5nIIXznwvpfK/2Jr433x6rtXJ9YJCpmDNZ94PYGadYT49Zj4Db1YgBv6L4fxGBr6VBjZXRayUDTZU7LZNALaXbYGrbrabbfY7a5h7YHZU5HYnZna0AXYsbXa3b3aqZPabYnJggJYfbICQS7AsZhD7B/a8AA5A44Gg67CqYQ5Q4sYw5w5KCI4MFsT94Y4iQKDY64747fZE6H5RbH6yAU4JYX76C3YoDWDWBM7RBi5s7JAc4cBc4EBQxki87WAC4UbC6jpsGs6G4sHS6y727y4hALDK7LD5DpDvCm7JZq667%2BH65m41CeEMCW4tA%2BHRFG71BzDO6BFLKTCJHJYZHzAlBRGu4KD0Ye6u6yZ35%2B4cBbLEDz6L7L6IFf7r6b6SIR474kA0gx4gGtYcakCJ5YDxAp6yYV5V7r78bQht7QhCaSAF7ubJb35qacA946b96GYmZmYWZ9YwF2YOYcBz6lbiJVjEpVjf6ojjDb5R4hbJYaEk5aExbyCn6U6qa6CnApZpY35l7e45Zd6P4j6khDiVEsC7EKD7H3CHHr7HGkg1aQH1ZtGnCnAdFLEQF1ZxDQGQkjD7HVrPIgnPJgmQZVHuaoETYYEzZza4Esb4GXBrYbYODEFBS7b7a4FMGYDHanYtK0GPYHAMGiGPZ4DPasFvYBaqCfbcG8C8E1AJaCHA6XAiHg45ISG8BSHw6yHI7yFgF8CY7KE4546KjqEH5XESDaGxZ3F6EgBPG07GDGGM6CHmFqaWH3KcAsi/oOH86C4uGi7wAS4xFS5%2BAy7tihEK7oBpEG7hGZC%2BlBlFCRE27ZEekW5245Dy7m7G5O7hku6O6ZGxm26Jl5ERkS5FFRa34fGC7%2B47EeZ7EHFHGiieTNFR7Qmx6gH6YJ6YBJ59Fe6DEgBmDr4wlEaiYCaJAwnQj16d4Fkaa2C96dGrCcYgCSBEZZ5Eb%2BDiaZ6SCZ5CY55cAmmcCnD5kP5Dmjle7%2BYDmblx5gHrAw7pDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/raillivore/skip.hpp)
- [unit test](../../../../tests/unit/raillivore/skip.test.hpp)
