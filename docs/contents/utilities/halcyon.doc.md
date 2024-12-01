<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Halcyon`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

## Description

`Halcyon` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Halcyon ::   template<template<template<template<auto...> class...> class...> class...> class...
          -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Halcyon
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RESULT;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    using UniWill = RESULT;
};
```

## Examples

- We will create a `Halcyon` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
template<template<template<template<auto...> class...> class...> class...>
struct Item_0;

template<template<template<template<auto...> class...> class...> class...>
struct Item_1;

template<template<template<template<auto...> class...> class...> class...>
struct Item_2;

template<template<template<template<auto...> class...> class...> class...>
struct Item_3;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Operation;

using PackedHalcyon = Halcyon
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using Result = PackedHalcyon::Will<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Halcyon`.

```C++
static_assert(PackedHalcyon::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<auto...> class...> class...> class...> class...Items>
struct Halcyon
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Tranquil>
    using Will = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBILcTC8RAAdIibod9kwFApEfDkaj0ZjsQZcUiAtgUQSMYiAJI/BQ3J7jYheByHAASYmQAE8BE8TAB2KwPQ6Cw6zRzIFECcaYVSpYjCvAAL0wAH0CHLFRAlk8hcc%2BYdiJgCOsGGrMKgqJiIFTXgpNQELDqACLcgVCsHA/6gyHgz2/d0Q33Qt2Br1%2B06whFEkk48lY4mktEx/EJvFx6MpqNkw4AFWIhgAjl46LSXYL6YzVQ6DUw6Dr7V5MkZDgR2alMMcAg7s7mGAWi6crSxE8STvbeU67c77tqgx7viHgwHZzP/VCl/PZ%2BHUOn44TYxnk5Gd0P97uk7uc/nC7Ri1OhfXwsBDgB1Oi0dudyvNPtuC89q/pkAQGbVsR25Hlx35R4HgAegAKnghDEKQ6CnjghDs2wIQsyEQ5EJQmCkMIvDJx2PYDjbL40AYTZUgIGlhweJ5lx9VcV29OdFy%2BTdtzTQ9eL3I90zpAgGSZAclQ0UDGIeZiONYlj2Nk7i%2BLJHjVJUg892E0TVXErgpKg551zY0M5MU4ywzhLcNNPVN1IE/ibzLMSfiVMwDKYiyzNM2SlKstTNLPY9BMjbTy0OcSAg8mSvN82L4s4yyIwc%2BygoC2yT2PMKmQAeVbXMGmi%2B40Pgw4ADE8GIcZDmwVRWHeNtiOk%2B570bZQmGQABrTB0FZWgOQEd8WTZTkGG5U4tSFcSNFIY4Swi1yUjm29BXEsxZsm1bXKixjhwnZrWsfIQvFSIoeoAJUwBQvFoVUTk7PL4mBbJxrcTaFteCSNvmvTvpWj6WDcv7tUi8bbn2wzDsOS7rtuob2q6nq%2BoGvwQBfWhr1OR6CpevbIOE57kCVBN4gICALkAhRWGVNEvhhm6CFm47ToyC6roZm5bXxgj0KETAqPQGq6t%2BRqEPwwyRTwImSdaCAEe63qRucEBMnVJZ33uw5JC5p4OBWWhOAAVl4PwOC0UhUE4N7LGsYU1g2CizACHhSAITQ9ZWTqQENjR4TMMwAE4AA4NADw2g8SAJJDMHlJESfROEkXgWAkDQZtN83LY4XgFBAGa3bNvXSDgWAYEQEA1gIVI4XISg0DeOh4kianOFUCOAFpEkkQ5gGQMUpD93gesIEg8HQPR%2BEEEQxHYKQZEERQVHUQvSF0FIAHdc1STgeH1o2Tfdi3OByuFq9VM1DjbxJO%2B73v%2B8kP3DggDwG/oWUdi4JZeALrQVggJB66pEbmQCgEBAHAJAMAKQ60aC3XiLnCAMRD4xHCC0dkO9eAoOYMQdkOUYjaH5gXF29c2CCBygwWg6CV5YBiF4YAMIMa524LwLALBDDAHENQyqhC8AADcrqHylPzOEWwXbhBeAbFetA8AxFzDgjwWBD4iTwCnZhpB%2BHEBiKzSsbCjDSKMO7FYVADDAAUAANTwJgdej1TYu0nsIUQ4g572MXmoQ%2Ba99DsJQNYaw%2BgZG50gCsVAtFshMPbhce6pgbaWDMJnDRxAx4CMCd0HhzgICuCmH4FIoRwhDEqCMFIRQsgCEyXoIpDR5jDASGMOoqTGgTDaJ4Doeg7B1L6K0Sp%2BTqm2AaaUsYDTOmLE/qsdYmwJB7w4MbUgGdeBZ0vh3LuPc%2B6HAHmYJ%2BuAR7vydp/b%2BhiVgIEwEwLACQNSkC9oEeEAcAixw0NHOOadDaJADgnDgSdSAp2dvCZIiQg7By4IkQ2kguCGyufHGZR9s62Dzq7Qxxcy7/wrqfGuoDwFv2bmwTgLQWC8J5O3Jg8ZGxcADvCLg8JzbDyIAk8eKR7HTycdIFxSg3Er10OtTeTBt7MImVM8FWcT5VzhIcC%2BWKcV4oJY%2BIlJKyVPxfkAt%2BxwnZmC/jCwuf8AGoFfvEWuYCNVypGCK3FqIjBEq4DNWBLwqqUCQSvLBaCMGkFtTgvBBCHD2pIYwAg5DKGHxoXQhhtAmEu1Yewzh5t8D6gcHwgRK8hHIBEfa8RdRD7SNkWghRWxzbKNUS7DRWilA6JDQ%2BWFximCmIsVYmx9raWONngy2Qrjl7m1ZZ4gxUSrCWD8TEAJpzgkNDCREjsbbrCxNmfExJ3aVitMjWkjJTT8jZIYOgQZBS0gZGKTkOdWTV3FGyMu7pU6GjtMaXkLdB7egDNyQsFdsxJibpaRe8oVTxkjIds%2ByRPLD5zINWKo1EriWko0Os/AlKFXO2VT/D2pADlHJGKcyRbyPnEtuTyEFPIeRRzMHHIF0zP2cBztCiDf94VIErmfbVqKm4tw4FixZg5eFil4ZKv44wh7AdHtS%2BeDiZ4SDrQvJljadAgCCOyzlu8XkfpXnypF58qCHBo93OjDGmPumqs/XVwDQMBHA7ChFFGQF13U2/EA9HTpKkYwHJUzGCDE2ICwLufA6AWoQda82jqqEuzc86whbqNWkM9RQqhYbMC0PoWIAN9rg16IzSw7hkb%2BFMPJaoYRLwE2CCTVImRcj2TpqUQk7NvBc3aNeIWgxqq%2BAmPMZY6xrZbG8Grdx5x9b%2BPuKEy24wPiO0ponRbEJEpODQQpkOmJcT4hUqSacs9M7F19OCIuvdZS10NBm%2BU3dl6n01J6AII9M3Jv1LmGtrp97%2Bg7YfXkoZk77ZjOGe%2Bg%2BknOByds7RhQ9HDjmfhFZoDmzQM7JVb/fZhzjmUAmQhkAgd4QBACIbH2QK04Q55D8nDd3IW53znss5/hiVoY0ES25XAAgAp5GYQFLyAi3cznh37kHJFmDJ7MinhGVgaMyM4SQQA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/halcyon.hpp)
