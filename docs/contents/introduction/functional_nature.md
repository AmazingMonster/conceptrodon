<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Functional Nature

I did not create the library with any functional concepts in mind, mostly because I was oblivious to the relevant knowledge.
However, the idea of composing functions is natural and familiar, as passing a lambda expression to a standard algorithm is already prevalent.
The library is based on C++ facilities and explained in C++ terms.
It is not an attempt to implement functional syntax on top of a primarily imperative language.
Knowledge about functional languages is not necessary to use, contribute, or fully implement the library.
Functional analogs only serve as an illustration of the underlying logic.

Haskell is the language we will be using in this documentation.
Functional analogs will only serve as illustrations of the library's facilities and will not be explained in detail.
For example, while lambda calculus is the foundation of functional languages, we will not dive into this concept since our illustrations will be based on the high-level abstractions implemented by Haskell.

## Types

The primary reason why we use Haskell is its type-check system.
We will employ the system to validate our compositions.

Consider the following C++ code:

```C++
template<typename...>
struct Mold {};

template<auto...>
struct Page {};

template<template<typename...> class...>
struct Road {};

template<template<auto...> class...>
struct Rail {};

using MoldInt = Mold<int>;
// Fails since `int` does not match `auto`.
using PageInt = Page<int>;

using PageOne = Page<1>;
// Fails since `1` does not match `typename`.
using MoldOne = Mold<1>;

using RoadMold = Road<Mold>;
// Fails since `Mold` does not match `template<auto...> class`.
using RailMold = Rail<Mold>;

using RailPage = Rail<Page>;
// Fails since `Page` does not match `template<typename...> class`.
using RoadPage = Road<Page>;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCcpK4AMngMmAByPgBGmMT%2BAOykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG4EAJ4pjKyYAHQPp9gmGgCCs8ReDgDUALKe6G%2BJkSVkSABFTlY3i9XnsDkdMKc3EwvEQHncnjCPl8CN9lExgJggSDgRCTlDXjC4YcmMcztSEUjLtdmGx0U9vsgDAoFOyTs83tifgAlVBMQHA0FkilU/Y0unnOWMs4otGPfmc7m89UC94ET4iph0YlSyEwmFeDJGP4AgCSgiBJzBNto6CR4QImPJMIA9D7vgAxI20BTfK3bIEANg0HpM0e%2B6FQmFDDFQuJYtOQCCjGlVqDjGgxb0t4WAeIJmHtuNOzvxhPdgi9MuLVrLdcwAHkIo7axWkVwm77/UG6KHw0SCwP44nk99U%2BnM9mC8ybmwC0XXiXrf9XV2J06XW6zgP%2BWboS3S99ReKdxKD9ej25b4O3n7A8Gx%2BEIwXn9Okym02%2BDMCCzHMGVpREVVRVA%2BWwTUmB5dcLVbK9g1vHtULoJFn1Pb1z03FDhWDdsMKIrCznbF9XjfEcQzDL8J2jSi/1necgMXMClQgpkrlXe4dXgxDow3LcywfEiayvMVH0o3CLA4NZaE4ABWXg/A4LRSFQTg3Gsawww2LYJzME4eFIAhNAUtYAGsQGUwszECAAODQAmUpzIxOSRqkkSN9E4SReBYCQNA0Uh1M07SOF4BQQDCiyNIU0g4FgGBEBADYCBSVFyEoNADjoeJIluThVA8gBaSNJG%2BYBkGQb4pDuMxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1ES0hdC4UgAHdiCYFJOB4RSVLUyytM4DtUWy3FUCob4ysjSrqtq%2BrGrMb4IA8Ar6GIIETK4FZeASrQ1ggJB8pSQqyAoCAPq%2BkBgCkMw%2BDoPZiFiiAYjWmJwmaC5Ft4GHmGIC4OxibQ6gSsz8rYQQu1oeHxqwGIvGAZFaBDBHSCwDMjHEIm8GITG8AAN2TNbMFUOpUR2MyPW6NbaDwGI5pRjwsDW/U8GC7heDZ4gYnSTAwX2QxgCFoxLLWKgDGABQADU8EwaaOxZKmeuEURxEGi2RrUNbJv0NWUD0yx9GF2LIDWVAUl6WKOHK2YjzBUxLGsMxIvljqsE9iA1lqepnAgVwpj8KbQgWcpKj0QpMgEVOc/SPOGCGLPRimhPen6SZPHaPRK4aOZS5GBIK7mAu24GZullb%2BPDO2CRlo4VTwrWqL9oqqqarqhrJCai7cEIEg7tMx7zK1tYEEwcVRjj0hbMkE47gCE5EkkDRvN80LlMjIIlI4QLSGC0y7kjLhIycgInPf5TJC4ZST5%2BQirwKKMU4rr0Sq9NKb0MpbRyj9P6N1ipsE4M0FgLNEjlSYPBa0XAAh3C4HcTSrUl7R26rIPq1tpC2yUPbcauhgazXmgjIeI9gHrQ4JtLKqJvi7W%2BGgjBWCcFljwQQohF0rqfRuivMwa9npJRgYg%2BIuVfqoGuqMARmCuRqzwVwMKNBaBgwhlDcaSM4ZUzMSjNGGMHBUxxowAg%2BNCaaWJqTcmlNZbU1VnTHYLjGbMzZv7YhXNkA8ypvze%2BmkhYizhuLXxT0OoyzMvLRWSgVa03VqWLWfBdYGyNibM2niLaUIGtQ2QdsxqaQYU7TWocrBu2ibHb2vssj%2B0DgQYOdTw6R3iNHdmXsug9CyC4Bg7ha55HTqM7u2cpq516B3VIRdejTPLoM5mAhq6tHGWnNZic%2BhN0zi3eu7dtnHK7ocnug91ibAHg9fyw9VrjXHpooR2jcH4MIRoBebVl7mFXk9DepAt47wSHve%2Bj9n74IvokABiREheTML5P%2Bo8nmcDAfFbJKV0qZW2iopRxBkE7DQVPFgCgWb1RZqIhEswWo/LIVNYpVtSlDXkLQypOgQAnBmnNBastWGPMihtOBO09rEuqqS8l3xKX4OpbiS6aipHxBXicORmL3oKq%2BnijVN0QDkpSCkAA%2BtKg1sqDVipBoY%2BIxjoawxRhY21qN0aYzsWo3GjiGAEzWq4smYgPFmRpmremfimb1ECRzEJYTPERMFsLUWFw4mS0SVTFJSt0mBqyZAnJBI8nG1Nowc2FCmUSDKcNNlDtOU1OMK7GwjT4DNL9pwH0QcXZh0sBHEBUdOr9L3g3JOKdTmTPQCs1uiyihZAWXMrIw767dHWfsgYCze3zpaNOzuNdcg7NmOcsoRy7kKH7gNflKLBUcH4cQFgJKyUUqpRBWY3zSErwegCyBm9t5YFBUPCF%2BQ7gnBOMpeyf9Qq/sSB/Y9IC0W2HAfIlYNkQCSHwXCjQeCL5cBOJGZSiQzC/3uScAV4HooQJekPZqYGOHPqI6QeWGRnCSCAA)

Restricted by C++ syntax,  we must declare the kind of parameters the template accepts inside its template head.

- The `Mold` accepts types, hence the `typename` and `...` inside `template<*>`.
- Similarly, the `Page` accepts values, hence the `auto` and `...` inside `template<*>`;
- the `Road` accepts containers, hence the `template<typename...> class` and `...` inside `template<*>`;
- the `Rail` accepts sequences, hence the `template<auto...> class` and `...` inside `template<*>`.

### `typename` && `auto`

To utilize the type-check in Haskell, we want to translate these declarations into Haskell types.
The translations for `typename` and `auto` are naive.
We simply define types using the corresponding names.

```Haskell
-- typename
data Typename

-- auto
data Auto
```

### `*...`

Then, we will translate the ellipsis into a Haskell type.
In C++, `*...` is the syntax to declare a parameter pack.
Note that the parameter list of a conformed alias metafunction in this library consists of precisely one parameter pack in the template head.
This restriction does not apply to class metafuntions.
However, conformed class and alias templates shall be undistinguishable from the users' perspective.

In the documentation of this library,

- `template<auto> struct Operation`,
- `template<auto, auto> struct Operation`,
- and `template<auto...> struct Operation`

are the same 'type-wise' in the sense that each of them is acceptable as a template argument for a metafunction with the primary signature `template<template<auto...> class...>`.
Thus, for the purpose of type-check, we will denote the primary signatures of `template<auto> struct Operation` and `template<auto, auto> struct Oparetion` as `template<auto...>`.

We will translate the ellipsis into a higher-kinded type of kind `* -> *`.
It will be a list-like structure.
For example, `0, 1, 2` and `0, 1, 2, 3` will be values of `auto...` where `auto...` is the type constructed by passing `auto` to the ellipsis.

```Haskell
data Ellipsis a = Empty | Cons a (Ellipsis a)
```

### `template<*>`

Then, we will translate the surrounding `template<*>` into a Haskell type.
`template<*>` accepts a primary signature and raises its rank by one. Hence, we will represent `template<*>` as a higher-kinded type of kind `* -> *`.

```Haskell
data Template a
```

We will drop the trailing type-parameter key (`typename` or `class`) when referring to a template template parameter in a parameter list since the key has no effect as in C++20.

Thus, `template<template<typename...> class...>` can be translated into the following type in Haskell:

```Haskell
newtype TeTeTyElEl = Template (Ellipsis (Template (Ellipsis Typename)))
```

## Partial Application

Let us create an ordinary C++ function called `charPlusPlus`.
It pastes three `char` values into a `std::string`.

```C++
auto charPlusPlus(char a, char b, char c) -> string 
{ return {a, b, c, '\0'}; }
```

What if we want to fix 'c' as the first parameter?
The result shall be a new function requiring two parameters.
When invoked by two `char` values, the new function shall paste them to 'c' in order.
In C++, we have a function called `std::bind_front` for this purpose.
We will name the resulting function `cPlusPlus`.

```C++
auto cPlusPlus = std::bind_front(charPlusPlus, 'c');
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGErqSuADJ4DJgAcj4ARpjEIACspAAOqAqETgwe3r7%2ByanpAiFhkSwxcYl2mA4ZQgRMxARZPn5cAZXVArX1BEUR0bEJtnUNTTmtQ929JWUJAJS2qF7EyOwc5gDMocjeWADUJutuTgoExJisB9gmGgCCG1s7mPuHVF4MHcy0l9d3t15pRl2zDYCiSTBWuxO6AOVj%2BAOAQNYmFB4KeUJAICSBhWCE8WGIChhPx%2BTC8RF2yAQ9WU3gUNP%2BEEp9V2TFIFKpxF2UTZTM5yFmuwAtJdIadQgjiQB2WE3XZy3ZnAhLBj7aWsrk8tlgNbxNwabUmSUAESJt0NJrNt1J5OQ9LptOeRtF6AxUVC6AA%2BlRiLJGRy7XatRxkNrZqbfjdQgRdiwmKFdhAw2bpT95RTFtGDm4s%2BzqbS7RBtSHeLsDZZtUHrKHntnDqWdW4GAb1jK02gyTWc7b87TC2tyyWyxZQ%2BHzRx5rROPFeH4OFpSKhONnLNZIYtlk8NjxSARNOP5gBrBJcAB0krMZkkZklAA5JABOKSXsz6TiSXgsCQaDSkWfzxccLwCggD%2Bu5zuOpBwLAMCICAmCqFUZIkOQlD1MAdKGJgtBCLiADus7bmgLBJHQTCOAIyiYdheF/rwREkfQcTAE%2BpD0XQsThEinB0agxHscQADyZI4ag%2BF7oECHIDcxDodxElVLU%2BCzrw/CCCIYjsFIMiCIoKjqOBpC6AEBhGCg1jWPoeBRMBkDzKgSTkQwwEcIKUIHEapgrpYZj/gAbrExB4FgNmJqQxBvI4bAACqoJ4IXzAo64rHoUKhJRYTUaJBG8LhxBMEknA8BOU4zuJAHYJJSGcqoN4AGyCrVki7MAyDILsUgnmYCbLlYlhsrghAkPsZjrFwsy8GBWizIeICSJIJ5cHVN4aLV36PnN6zxIkk4cO%2BpCfqNJ4aJIGj3sdkrrKtS0BLRC5ycBoF7vMUGwfBiFEGQFAQGhGEZSJYncDxfEGI56VYf9t1sYxKAmcxj4/lDHFcYBrG8QxsRCcINHiW9Ukyc5vC44poRyapwiiOIWlk7pajiboL6w2ZXk2LQVnxQuDkZM5rkENC6weeZ3l%2BQFQXIvA8zhYIeDRbFtDs4lSzJW0vNpVREOFTleUFYDxUcNOv5lZwFXvUNNX1Y1FKw%2B194LUd3WCzYuwDR9w2jeNO5PfMCDnPilC63tB1mEdtVcBoZg3pd8SPlwZhbQbBkAUBeiTRBL0QEguNVSh3342DmUA4RaOkaDavYwZiNxL5yBJEkHq%2BVw94eiDyIEB6qiNajwNI2wckV5j6sGbj0mySjRMq8p2nkxpEjSNTSi0wZujrPohjGA7lnWeLHOOc5AD06Keb1Fg%2BbwqD%2BcQgXBVvkuRZgMVxVvCsbil495wP265flGu6/rt3lZVLt25NRYAoKuux6422bice2zN%2Br4Bdlud2KdpqkG9kwX2oUdoBxAJdE8N57zLVqrVfBy0NAN0uvHf890QIe3Aigo8kgbydUlJKeI54uDxA0DeNhUdpA7XWKVBOclkG6zMIIqhKMRGkHPmkZwkggA)

Note that the logic behind `std::bind_front` is independent of `cPlusPlus`, meaning the process of binding fixed values to the parameters of a function is somewhat canonical.
For a function requiring three parameters, there naturally exists a sort of functions requiring two parameters, obtained by binding a fixed value to the first parameter of the original function.

Such naturality is better shown in Haskell since no external function (such as std::bind_front in C++) is needed for the binding operation.

```Haskell
charPlusPlus :: Char -> Char -> Char -> String
charPlusPlus a b c = [a, b, c]

cPlusPlus :: Char -> Char -> String
cPlusPlus = charPlusPlus 'c'
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:32,endLineNumber:16,positionColumn:32,positionLineNumber:16,selectionStartColumn:32,selectionStartLineNumber:16,startColumn:32,startLineNumber:16),source:'module+Main+where%0A%0AcharPlusPlus+::+Char+-%3E+Char+-%3E+Char+-%3E+String%0AcharPlusPlus+a+b+c+%3D+%5Ba,+b,+c%5D%0A%0AcPlusPlus+::+Char+-%3E+Char+-%3E+String%0AcPlusPlus+%3D+charPlusPlus+!'c!'%0A%0AcPositivelyPlus+::+Char+-%3E+String%0AcPositivelyPlus+%3D+cPlusPlus+!'%2B!'%0A%0Amain::IO()%0Amain+%3D+do%0A++++print+$+charPlusPlus+!'c!'+!'%2B!'+!'%2B!'%0A++++print+$+cPlusPlus+!'%2B!'+!'%2B!'%0A++++print+$+cPositivelyPlus+!'%2B!'%0A'),l:'5',n:'0',o:'Haskell+source+%231',t:'0')),k:59.793739170473714,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:40.206260829526286,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

We apply a function requiring three parameters to one argument and obtain a function requiring two parameters.
Since the application is not completed until the other two arguments are provided, the process is called 'partial application'.
