<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-amidst">To Index</a></p>

## Description

`Typelivore::Amidst` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amidst
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = Amidst<int, int*, int**, int***>::Page<3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
There are two ways to achieve it.

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target element.

We will need the desired number of `void*`s in the front of the function's parameter list to enumerate the unwanted arguments.

`PointToVoid` will turn an index into a `void*`.

```C++
template<auto>
using PointToVoid = void*;
```

With its help, we expand a pack of indices to produce `void*`s.
`Midst` will help us extract the pack from a `std::index_sequence`.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    static constexpr auto idyl(PointToVoid<I>..., auto* target, auto*...)
    { return target; }
};
```

Now, we make a template that generates the `std::index_sequence` and translates the result.

```C++
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(static_cast<Elements*>(nullptr)...)
        );
    };

    template<auto...Agreements>
    using Page = std::remove_pointer_t
    <typename Detail<Agreements...>::type>;
};
```

- [*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbBqkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimImujMh4mArnO4cnZ/ufu2/HR79mAGZgshvFhziYAW4vI5aIQAJ4Q7B/cxAhggrxgiFuZBDdBYKiI5HvL4k75/D4bc4ASRYiXobEETGqL22PwppK%2BP3JO3OylQwQIABVUAA1fnoFlbH4ETC0gwyrFMaGoQknLypIy8/mCYVivASiGXc4AN3FGwhVhO3IuAFl9UNJQc/jK5UzMFiCHDbsw2KrjkNiF4HOc7egHSYAOxWCOXC1E44uulurGpABemAA%2BgQAHS5ql%2BgNBggh%2B0EFMEdAgEDBLCqDNKACOXnu7shVNz2cJAKRVqjf3OA/OE0cyHOaAYQ0wqkSxHOSqI531cNoED5At14qx%2Be7HdIc%2BVlOGwEwBD389QGw7s37g8jFnOxBPSwY5yPJ4t4JjyK/AMtv2JFzHCwpaOtKspJgqkKet6rCYB22D0owBAKAWBCBsGQGlt%2Bf6Dq%2B4Hyq2bhppmxbbj2xy4YWwbXHUdA3gOd70bh5zqsEwCvl6mDggCRpYCC0HuiczGDhATHCQOoZDOWlYgCwTAANaZjWU71pgTYtluXbkeJzFVkuK7DngyAZqIUmQghspIQo5rdhADBeLQtCJGhsxXmJg7Xr%2BTGRrGXlWkJg6JgRirKh2xzAI%2BlmCCh3ZMaxmrKEwx7cUauJVo%2BLCoMambJAK0RZt5UGcT6XE0UwdGQuFkUMshHaIlWAldn%2BPlxv5pwcmSAFbOc2CqKwdJca81odVK8YosCoJcVi44rM5MXkcNlJCF4iS5Jg6AAEpPA5xZDWqGrsctq0pOtW0KDtKWLoI2ytf%2B7UXGdF17cc8XsY9tDFoa5yYWGZaQgKe4ChsgPXcDV0EDd3ZVolx5YgCTXxhS5yCk8u2sn8hnGUwChKA0EBpSACiwRm2NYu9p7nEda2bdtH2Ip5f4cPMtCcAArLwfgcFopCoJwbjWNYQ6LMsU2AjwpAEJoTPzPJICs5I2YaAAHGYZgAJxq1wrPK0rXARhG0gsxwki8CwEgaAknPc7zHC8AoIAJJLXNM6QcCwDAiAgIsBCJNC5CUGgtJ0NEoSwZwqhK7EAC0sSSOcwDIKOUjZmYvDrYQJD6no/CCCIYjsFIMiCIoKjqM7pC6K0ADuxBMIknA8MzbMc1LPOcAA8tCvvFqgVDnBH0ex/HifnMnZjnBAHhB/Qs4olwsy8E7WjzBASCB4kwdkBQEDr5vIDAFIZh8HQMrEPbEARK3ETBPUcIN7w1/MMQcLtxE2iYA49%2BkIHNXtwwtB33LlgCIXhgBuDELQe23BeBYDkkYcQQC8CPgcHgbKUDuZTg/tCVY4s8pG25rCCItdn4eCwK3NCeAzbQNINlYgEQTrXDgcAWERgpbzCoAYYACgRSPCru3b0X8c7CFEOIQuQiS5qFbpXfQhhjAC0sPoPAER7aQHmKgZy6QoFR1xIaUwlhrBmGtrQ4g%2BonjwHmHYD%2B1QXAMHcJ4Zo/hbFTD6DEVouQ0gCFGC0JIKQPEMGcSUfo4xKhWI6MMRo9ixhtFCQIToDQAkzHGOErxegJjxOCL0QJriLHCxWBIJuHB2akCtrwG2/dI4xzjgnJOCtx4QFwBnWeYsF4SzYfMBAmAmBYBiBAGWIBJAAmzGrAEBsNCSDMJIeIGhWaxDVvoTgJtSBmwBFwbMsQuCxCVmrXWsR5Za2GbEYprcbZ2wdq052K8Pary9l3P229d4z1DmwTg9QWDGgjFHJgY4DCai4GrbMqyMH4CICYysrQhF51EdIcRShJHl10EfGudd74FKKSUtuHBO4%2B2hOcXu5TB5xxBLI0e/zAUTynhvGe4JARmBaUvF21yHnRH9jvVA09%2BhEqMH8rgCQaAfWiOfS%2B5dH63y/iK5%2Br936f2oT/JCf8AGt2AaA8BjkoHi1gbIhB3N8DIMcGg1umDkDYK/ng1uhDiFwlIasbmFCqHi1ofQpQjDNVsTYXwTh3DeH8MYII2QkKC7QtkBIsu3MEUyNYXoqwCjCEqN6TzDRAgtE6J4pGgxRjoigrMao6JKDnAQFcCk1ogQMnTCCT4vI6RC3lr8Qkstljc01GSZE7x9bqhxO6CWlxqSm1ZBbeE2t2SFhLDyfPeZhSW7lzKQPSp3ziV/IBYrCeDSQXUpWXStppAOldP6HGo2izln/LGRGVmat9YAnGZMyQrR0UnNsGc%2Bllz4DXO9t3FlTLiBPNWK8oeLAFDGlHMaedBEhhp2BZnMFRdhH5wkIG4usKQ06BAACUgSL67QNRRO62Hdbk9z7qoH9f6ANAbdA6SebLKXRFXQCddFzXZr3I5vN9DGZ4gH/atDMgG1YZmAwQDM%2BHoUnwFZQIV3NxWAPFmJyVViv6ysEPKwB2rMAgLARAtVMDZSautTApBoT9Xl0Nca6hpry7mtvla8hJi7W8AdQwjT8DXW0Y4UlT1mA%2BECOoRCkRAbIPBqkUh8Ncj9HRqUbGtRCaJycDWGlVNlhDGlOMaY0LObrH5tsVW4tRQu1uN8dUKt7jqgDtSSEht7aq2trCZMTtWTu1dDK/2qriScnDoLhho5k7OD9wI/%2Bk0xGZSkeXSQVd89F4bq3d0ygBT90gHVtmAEAJWbayvRbObEZNltaw7bO9jsN2y0kKzIZesIwWyVpITWXAVZmEOUbAEmHSmcBGxcgpqd1t3c2w%2B%2BYtDUjOEkEAA%3D)

- Second, we use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target element.

`Prefix` will turn an index into a constraint that evaluates to `true` for every type.

```C++
template<typename, auto>
concept Prefix = true;
```

`Midst` will help us extract the pack from a `std::index_sequence`.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<typename Target>
    static constexpr auto idyl
    (Prefix<I> auto..., Target, ...)
    -> Target::type;
};
```

Now, we make a template that generates the `std::index_sequence` and translates the result.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};
```

- [*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbFykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn4JdpgO6bX1BIVhkdFxrXUNTdlD3b3FpYMAlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYia6MyHiYCmfbB8enex87r0eHP2YAzMFkN4sGcTP83F5HLRCABPcHYX7mQEMYFeUHgtzIBQEdBYKgIpFvbZnZTETA0VTPLbfAiYFiJAx0zEEWE3ZhsUhnJhQ1CE45oVHXAik8mUsH/C5nAjELyYcFWY6/d6fVWbb4qs4ASQZ9DYgiY1Wp6uVarN%2ByJJxJAFk8OgccaLcc6brDfKIaz2ax3YjjjjZQ4zrb7SKTAB2Kxhi4Ky0uxluzGpABemAA%2BgQAHRZrX8o7%2BryB4M4xO4kAgYJYVSppQARzlQsxWqzGcJ/19PwjvzO3el9PjzI9bMY3rOABV6sBMARcz2zjjDXhkGdBTjMKpEsRubyznbYbQuz2IGSKXhVI2EVuiM2uePiJOCFzmzMD92ALQX2/3sue92KjvR/4/1Nc4jhYO0HReX44yZd03B/DlMGbbA9UYAgFFzfNA1A8DpyVTtjlnaCEwhZM0xFHM2xfOcZQLEUrjqOgqPDP9Z1nLxUiMaUhwlKUsGBH8qNnCBBNY7si2nEjSxAFgmAAazTCs12rTA6zuWCKMRSiCNE1iy13WgIBxdBvyHVM7VQuFMWQ%2BlUPQyjOyjJ8RO7Z9AKYqMYyVbTuyIgc3B5K8syOYByRswQ7PbNiOOAUkmEnHjLinJhGIhYLQv1NDmwREybk8/88uA80TWJc5sFUVhGUwR0NSKmlLWRIEQSqzFBWWRI0NzQr1jOIQvESXJMHQAAlR4vFoEVIOOdjghi3r%2BpSQaRoUMbQ0lHdBC2AqSs2M4lpW6rfmmzi9vGhLsJDTFggfdaCHWLkrs2e6Ns2bKQGUOLYP%2BVsgO27rR0eCa6r9OpHGQVMmAUJQGkMqSFG9cG7LcE7rrmgbhtG8aEVcv8ODmWhOAAVl4PwOC0UhUE4NxrGsOcFiWZqAR4UgCE0XG5lkkACckDMNAADjMMwAE5Ba4Am%2Bd5rgwzDaR8Y4SReBYCQNA0UgSbJimOF4BQQBVlnSdx0g4FgGBEBABYCESKFyEoNAGToaJQm9ThVF52JX1iSQzmAZAlykDMzF4QbCBIO09H4QQRDEdgpBkQRFBUdR9dIXQEgAd2IJhEk4Hg8cJ4nWfJzgAHkoUtkVUCoM4Xbdj2vZ9s4/bMM4IA8O36E3ZEuBmXg9a0OYICQW3EntsgKAgIeR5AYApDMPg6DpYhtYgCIC4iYJ6lhbPeDX5hiFhIuIm0do9aZ22MqLhhaE3pOsAiLxgH82haG17heCwGSjHEG%2B8HJDoADdHgFzXO0KEKwmZXUqAXGEEQM57w8FgAuMo8CK1fqQABxAIgLSuB/YAMIjCszmFQAwwAFAADUHipyLuyLesdhCiHEDHcO8glBqALinfQhhjDU0sPoPAERtaQDmKgdq6QX6viMuCC4phLDWDMOrdBxBzICIgHMNoHRnAQFcKMFopBAjBD6CUAYCRchpAENonIKRTEMEmP0GIrRKjH06MMRonhmh6DUdULoDQbGGLsbYZx5jxjeP0VMIxqi6bLAkLnDgRNVYFw1lXV27tPbe19tzJuEBcDBw7ozbuzMCFzAQJgJgWAYgqNIBzSQ/wMyC3%2BNLDQkgzCSFiMrAmsRBb6E4PLUgit/hcAzPEWIvNBYS1iFzUWtTYhxKThrLWOt8n637ibAeZtS5WzHhPdujs2CcHqCwP%2BYZXxMGXAYTiXBBYZn6WTIORBFHGQSEwyODDpBMPjqwpOuhZ7p0zlvaJsS1a8A1iXC2UIzgV0STXT2wJOENwuVc5urdh7tzBACMweTe4GxWZs6I1tx6oDbgMaFRhzlcBVjQca0Ql4ryTjvDeNDaV7wPkfBwNCz6oQvlfAut976P2fjQ9%2BnCv5k3wL/RwACX7XNUCAukNCIGyzJtA2BsJ4ErDJkglBTN0GYKUNgwVM0CF8GIWQihVDGA0MefQ6OLzZBvMTmTT5HD8HSKsDw6ByihEiIEGIiRkpnWyPkdEO5gDBEVCqOkFwDB3CuLGLoyNPjpjGMsdUQJSQk3pHjUY0NjiBBeJcVkHRHinETBCbY9xATo0FucRmux4TFiRK7p0mJ%2BcZmcAhckk5MLzmXJ5s3LJtyUV9PRQU0gRSSkDHKbLbpvSLkNLDATQWUt/iNOaZIBIALC6a1sPMjFSz4ArPNmXXF2LiDbJWHs2uLAFB/yXH/LtMEcSB3wLc0ODzZBPKtbQ21bCQD/FIN8rOr8/nNvVsXNZ5dK6qAvVem9d63QOhbvipF0QB3/CHYsw2g9EMjyPVh9uIBr39VTLewWqZ70EFTJBl589KWUGpWTBl18mYMaZcfVl%2BLz6X2vsKzAd8H5iD5aggVn9VVvx/o48VQCpXIFAbKwQkCk6Ko3iqxBiiNW8C1Vg%2Bker8HoaIXFY1mBKHUNQRaqOEhrVxxYXanQP7HVcJka6vh7ryaeoYC/VYRkUDcIsHIwFCilHwFUQ49RfhNGRpTXooopbE15HSCmkx1Rq3uOC548t%2BbkthpzVWktviy3dBTfOYJUXcsNoUBE6OQHpkgY4FXKD16zjEYzGR3tT6SADq7j3Ydo7SmUGiVOkAQsMz/H%2BATMWq7lbDbDEMqrgLOBzN1sOypBMamSzDMrXmkgRZcH5mYKZst/jAdm5und0SA4zY3Z1xZcx0GpGcJIIAA%3D)

The function is implemented using concept expansion in this library.

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/amidst/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/amidst.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/amidst.test.hpp)
