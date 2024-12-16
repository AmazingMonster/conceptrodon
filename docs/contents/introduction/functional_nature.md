<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Functional Nature

I did not create the library with any functional concepts in mind, mostly because I was oblivious to the relevant knowledge.
However, the idea of composing functions is natural and familiar, as passing a lambda expression to a standard algorithm is already prevalent.
The library is based on C++ facilities and explained in C++ terms.
It is not an attempt to implement functional syntax on top of a primarily imperative language.
Knowledge about functional languages is not necessary to use, contribute, or fully implement the library.

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCcpK4AMngMmAByPgBGmMQgAMwapAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9NsA1B6pAJ7EeMAIBHtmGmaSewBijMB7ALKoVIYmGgCCu3tCygAIgANAC0YU2DCUoIAklhBHgaCM9t9UkxkAhMKCzAA6DRfb4EgiYFipAzEkyJNwEI6pRisTA4pmU7AE8bELwOV6edB7EwAdis/MBlKsPyJJLJTApVKYXiITJxLLZBA5XOUTGAmD5goFIsSYsJP2JpPJmEp1MlZotNLpzDYipZe2QBgUCkdiVZP3ZnMuACVUExeQKhfrDRLTdLzVSTVKZW45QrmZ7na73cmvd8fVy/Uw6DrQ6KCQSvJkjNzaOgYYI%2BYlARX0BbwgRlQaCX97nnaAo9mXNnyAGwaZsmId7dCoTA9hioS4saUYwcaROoUcaJU/UvhZ4arXVy6U%2Bu76NuEeeovizdlneazAAeQitaPt4tXFbho7XZ7fe1a7fY4nKc9hnOcFwQJdbXpNg1w3b4t3LN5KwfX86wbV932LK9tz2AMg0Q4NUNwxsqXwjCfk/Ohv3Cfs11IgDJ2nWc9nnAhFzXWNrVleVUA9bBUyYN0YJLa8cK7fCn1EugLVI8820vOCRNzOhjwkpTaAtY8yN%2BfZO0o3tqN/IdNPooCQOYsCIKtKMbVpKDGQzfjBKHWD4OeIiVMPHDA2ItxNNkiwOBWWhOAAVl4PwOC0UhUE4NxrGsXs1g2X8zESHhSAITRApWABrEAQvXMxAgADg0AIQuKgdEkkMx%2BUkAd9E4SReBYCQNBSCKopijheAUEAUkyyLAtIOBYBgRAQDWAhUnlchKDQUk6HiSIGU4VRKtBAc7mAZBkD2KQcTMXhMHwIhTnQPR%2BEEEQxHYKQZEERQVHUIbSF0LhSAAd2IJhUk4HggtC8Ksuizg73lGbLnePZ1oHTbtt2/bJEOvYIA8Rb6GIPlUq4JZeEGrQVggJAFtSJayAoCBSfJkBgCkMw%2BDoYliD6iAYhBmJwhaI5/t4TnmGII47xibRMAcXnSAWthBAfWgederAYi8YAE1obsJawecjHEBW8GIMXHAANynEHMFUMX5S2dLmzqEHaDwGIfsFjwsBB1U8Fa7heGN4gYgyTBARJQxgHtowspWKgDGABQADU8EwT67ztCWruEURxHu1OnrUEH3v0YOUHiyx9AdvrIBWVBUgaPqOFBcZiMBUxLGsa5eFQH3zpN8vugN7IXAYdxPA6PRQnCIZKhGD6iiyAQpj8KeMhnhh5mGBIPrsXuBD6SYh/yde6k3xoJgGMeFkn2xj7nvRZlaFeJ7XlYFCSzYJEBjgwtITq284GGNq2vYdp7QOmYVGuBCAkGxmlPGGVw4rExEGEYEBcogEkIkHEAREh1Q0DVeq7UQoDiCMFDgzVSCtTSjiAcXABzFQCMVKhIVJBcBChghqX9QY9VsP1GBQ0ibjWJpNCGs1KbU0xitNgnAWgsENvyUETB%2BLli4AEHEXA8THVOiQPAF0PqpxuhnaQWclA51eroBm31fq8zfh/Nh3VwbTXlHsaGkjpGyPkc8RRyi8So3RmTTGkCzDQIJsNfhIj4hzSpqgDGIwnEyJdMHRRXAUg0FoMzVm7NXr825hLDJgthai3Fl7SWETpYEFlvLKKitlaq3VgUzWwcdblL1r3Y2NcopmwtsSCWNsiFRXto7bmLsthRXdp7dKPs/ZKEDlrEO25w58CjrHeOidk4FJ0enO6%2BjZDZxelFEx%2Bcw5NysMXXpZckHRSrtkGudcCANwOS3LqHdNFd1ORvBwfcICuCvh9Ue5RV56Gng0T5aRF4NDvosfePQt6X13vPHurzIVzFPr89eUK8gwpvifH599X6rHWC/XGjV37A1et1PY0SXGxIUUolRGhQHqKxuYKB%2BNYGkHgVgBIpyiEkLIUo7B/JmH8n5NVW4W0PrWM4L1LhgTeHwH4VNSGYSQnEDEVsSR/8WAKENntQ27izTjDUeA86l1ZC6PWQ9eQhjtk6CSF9H6f0vaWKJV1MGgioZUFJcQFgaqNVap1VGcYXiIk%2BPiJAxIATZnBMDeTBVkbMYgE1akVIAB9bVARE26oIIm1V%2BimbxFSRzLmgsskFqFiLA2EspaMBKQwOWIMKkqzENU9KtTtaDN4PgfWrzmmm3NsgS2nTBC21er0p2RwBlu1OCM728RxkByDtrGZPC5magWQnJOjAU7GrWRIDZj0LW52tQYfZRcbDHPgBXc5Aga7bHroXZulhW7RQeVgE5j8D5wr8O8gegLvnjzBUC4o2RAX/OyKC8%2BLyGjbzaNC6%2Bb6IPH1A2vC%2B/RAXooQ9ip%2BuK7oOs/iDElWbmLer2CmnE6baUGsgbjJlPC4GYAQeyt%2BXKCg4kSIkEKBVGHtRY/yahOHiXis4QNZleVJBKIFRoRR2CuCJAHCFfkZgGEEsSI67%2BHCpVvyOrxp1qnmU%2B0yM4SQQA%3D%3D%3D)

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
data Ellipsis a = Empty | Dots a (Ellipsis a)
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
type TeElTeElTy = Template (Ellipsis (Template (Ellipsis Typename)))
```

The primary signature (`template<typename...> class`) of its parameter list can be translated into the following type in Haskell:

```Haskell
type TeElTy = Template (Ellipsis Typename)
```

We will abstract template instantiation into a Haskell function.
Since we will only use it for type checking, we leave its body undefined.

```Haskell
instantiate :: Template a -> a -> Typename
instantiate = undefined
```

Suppose we have a metafunction of type `template<template<typename...> class...>` and several arguments of type `template<typename...>`.
We will see the instantiation process of C++ templates translated into our notations.

```Haskell
-- template of type `template<template<typename...> class...>`
tem :: TeElTeElTy
tem = undefined

-- arguments of type `template<typename...>`
arg_0 :: TeElTy
arg_0 = undefined

arg_1 :: TeElTy
arg_1 = undefined

arg_2 :: TeElTy
arg_2 = undefined

arg_3 :: TeElTy
arg_3 = undefined
```

We must pack the arguments into an `Ellipsis` before instantiating `tem`.
This behavior is consistent with the actual instantiation process in C++. According to the standard, `template<template<typename...> class...>` declares only one parameter, the pack `template<typename...> class...`.
Any given arguments must bind to this parameter pack at the beginning of the instantiation.
We will do it explicitly.

```Haskell
pack :: Ellipsis TeElTy
pack = Dots arg_0 $ Dots arg_1 $ Dots arg_2 $ Dots arg_3 Empty
```

Finally, we instantiate `tem` by the `pack`.

```Haskell
result :: Typename
result = instantiate tem pack
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:1,endLineNumber:44,positionColumn:1,positionLineNumber:44,selectionStartColumn:1,selectionStartLineNumber:44,startColumn:1,startLineNumber:44),source:'--+Copyright+2024+Feng+Mofan%0A--+SPDX-License-Identifier:+Apache-2.0%0A%0Amodule+Main+where%0A%0A--+typename%0Adata+Typename%0A%0A--+auto%0Adata+Auto%0A%0A--+*...%0Adata+Ellipsis+a+%3D+Empty+%7C+Dots+a+(Ellipsis+a)%0A%0A--+template%3C*%3E%0Adata+Template+a%0A%0A--+template%3Ctemplate%3Ctypename...%3E+class...%3E%0Atype+TeElTeElTy+%3D+Template+(Ellipsis+(Template+(Ellipsis+Typename)))%0A%0A--+template%3Ctypename...%3E+class%0Atype+TeElTy+%3D+Template+(Ellipsis+Typename)%0A%0A--+Template+instantiation%0Ainstantiate+::+Template+a+-%3E+a+-%3E+Typename%0Ainstantiate+%3D+undefined%0A%0A--+template+of+type+%60template%3Ctemplate%3Ctypename...%3E+class...%3E%60%0Atem+::+TeElTeElTy%0Atem+%3D+undefined%0A%0A--+arguments+of+type+%60template%3Ctypename...%3E%60%0Aarg_0+::+TeElTy%0Aarg_0+%3D+undefined%0A%0Aarg_1+::+TeElTy%0Aarg_1+%3D+undefined%0A%0Aarg_2+::+TeElTy%0Aarg_2+%3D+undefined%0A%0Aarg_3+::+TeElTy%0Aarg_3+%3D+undefined%0A%0A--+create+an+argument+pack%0Apack+::+Ellipsis+TeElTy%0Apack+%3D+Dots+arg_0+$+Dots+arg_1+$+Dots+arg_2+$+Dots+arg_3+Empty%0A%0A--+instantiate+%60tem%60+by+the+%60pack%60%0Aresult+::+Typename%0Aresult+%3D+instantiate+tem+pack%0A%0A--+error+silencer%0Amain+::+IO+()%0Amain+%3D+return+()'),l:'5',n:'0',o:'Haskell+source+%231',t:'0')),k:59.793739170473714,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:40.206260829526286,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

The `result` is of course undefined.
Thanks to Haskell's lazy evaluation, we are allowed to talk nonsense.

## Partial Application

Let us create an ordinary C++ function called `charPlusPlus`.
It pastes three `char` values into a `std::string`.

```C++
auto charPlusPlus(char a, char b, char c) -> string 
{ return {a, b, c}; }
```

What if we want to fix `'c'` as the first parameter?
The result shall be a new function requiring two arguments.
When invoked by two `char` values, the new function shall paste them to `'c'` in order.
In C++, we have a function called `std::bind_front` for this purpose.
We will name the resulting function `cPlusPlus`.

```C++
auto cPlusPlus = std::bind_front(charPlusPlus, 'c');
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM1ykrgAyeAyYAHI%2BAEaYxCDSAA6oCoRODB7evv6ByamOAqHhUSyx8dJ2mA7pQgRMxASZPn4Btpj2BQy19QRFkTFxCbZ1DU3ZrQojvWH9pYOSAJS2qF7EyOwc5gDMYcjeWADUJltuTpPEmKzH2CYaAILbu/uYRydUXgzVAmLXtw/3XlSRgOzDYCkSTHWB0m6GOVnufyYXiIB2QCHqym8CkxgIgaPqByYpFR6OIB2ixPxZOQCwOAFprtCCMQwsAjgiAOzwu4HXkHC4EVYMI5conkykmDkAEThf0lMoR9yRKOQOOxWNeUqZ6BAIGiYXQAH0qMRZHjSWq1cSwBxkDaFrLFXcwgQDiwmGEDhAHZzuXzUStXcc3MGSRisWqIDa7bwDjbrDbrZtLPbXiGTnHNgBWNwMeNbP18tDItOh1URrFR5MWROZhMcB0FuXShv6ThZ3h%2BDhaUioTghyzWaErNYvbY8UgETQNpYAaxAWa4ADoOWYzJIzByABySACcUnXZjbHEkvBYEg0GlIXZ7fY4vAUICvU%2B7rbgsBgiBAmFUVWRJHISh6mAbFDHaIQEFQAB3LsJzQFhEjoJhOmUMDaAg6Cb14eDEPoeJgAPUgcLoOIIlYDZsNQBCSOIAB5ZEMJg6cgl/ZA7mIEDOF4H8qlqfAu14fhBBEMR2CkGRBEUFR1FfUhdECAwjBQaxrH0PBokfSAllQRJOkfDg6RhY4pVMQdLDMW8ADc4hZLBNO9UhiA%2BRw2AAFVQTx7KWBQR3WPQYTCVDwnQyCmO4XgoOIJhEk4HgllodtO2Yu9sFY/8yVULcADY6SyyQDmAZBkAOKQlzML0BysSxiVwQgSCOMwti4BZeBfLQFjnBJJCXLhsq3DQssvfdJEkLYsyzY9T1Ic8mqXDRJA0Xd5o5LZBr6wIsN7LjbCfSdpyWd8vx45B0sAiBgNA4LGNgyjqIMFC0Ou5jiLwlBFII/crxe0jyO2766IY0LNuO9jOPvFjeIIfjtqE4RRHEcTYaktRmN0I93uUsybFodSvN7XT0n0wyoeM0yqosCzeFQaziFszA8acwQ8DcjzaDxnzVj8wIAoYILwKB2KIqimLwvixLr2SzhUr/IgMuy3L8r2Qw2S4XcermiqVOqg5atlhqmpavbXw60gEEuLB4gchKTzPEAtjMOasq4DQzC3Vas33LgzHGiXZLvB9drat9PwgJBjtOihzo4y7%2BcwwWiKo3DkPSPmQrj2T/pASzkESRJDUs1XDXu%2BmCENVQ8oTu6frYP7E5o%2BjhAF2SQej7bjr4sIYdkESEekJGlBR2TdC2fRlcx8m1I0%2BBtIJgR9IAehhcfrEp3sabphnnOZzB3M86flk5sThn41OnvC0hIuiwWxY4DtfdvKW0r18v8pYBRs4OAu1eLyZNaxmr8B63HIbIOJszZMAtpQG%2BU0ZpZSXFuXc/UspZQQf1DQqtVr3ypttR8z59qdUkFuMqHIORZlXFwLMGgtxkI9tIa2Wwkp%2B22qAm%2BZhGEP3Biw0gNNUjOEkEAA%3D)

Note that the logic behind `std::bind_front` is independent of `cPlusPlus`, meaning the process of binding fixed values to the parameters of a function is somewhat canonical.
For a function requiring three arguments, there naturally exists a sort of functions requiring two arguments, obtained by binding a fixed value to the first parameter of the original function.

Such naturality is better shown in Haskell since no external function (such as std::bind_front in C++) is needed for the binding operation.
First of all, we recreate `charPlusPlus` in Haskell, where a string is equivalent to a list of characters.

```Haskell
charPlusPlus :: Char -> Char -> Char -> String
charPlusPlus a b c = [a, b, c]
```

Now, we apply the function to `'c'`.

```Haskell
cPlusPlus :: Char -> Char -> String
cPlusPlus = charPlusPlus 'c'
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:1,endLineNumber:13,positionColumn:1,positionLineNumber:13,selectionStartColumn:1,selectionStartLineNumber:13,startColumn:1,startLineNumber:13),source:'module+Main+where%0A%0AcharPlusPlus+::+Char+-%3E+Char+-%3E+Char+-%3E+String%0AcharPlusPlus+a+b+c+%3D+%5Ba,+b,+c%5D%0A%0AcPlusPlus+::+Char+-%3E+Char+-%3E+String%0AcPlusPlus+%3D+charPlusPlus+!'c!'%0A%0Amain::IO()%0Amain+%3D+do%0A++++print+$+charPlusPlus+!'c!'+!'%2B!'+!'%2B!'%0A++++print+$+cPlusPlus+!'%2B!'+!'%2B!'%0A'),l:'5',n:'0',o:'Haskell+source+%231',t:'0')),k:59.793739170473714,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:40.206260829526286,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

We applied a function requiring three arguments to one argument and obtained a function requiring two arguments.
Since the application is not completed until the other two arguments are provided, the process is called 'partial application'.

## Currying

When I said that the Haskell version of `charPlusPlus` is a function requiring three arguments, it is inaccurate.
As we already saw, when supplied with an argument of type `Char`, `charPlusPlus` produced a new function.
In C++, we don't treat functions as values. Returning a function is not supported by the language.
However, for a pure functional programming language built on top of lambda calculus, values are represented as functions.
We will briefly introduce lambda terms and translate `charPlusPlus` into such a term.

Lambda calculus abstracts computation and provides a simple model to express complicated logics.
Lambda terms are the building blocks for the computation representations.
Informally, there are three kinds of lambda terms:

- a name to identify an abstraction point (`x`),
- a function to introduce an abstraction (<code>&lambda;x.&lt;body&gt;</code>),
- a function application to specialize an abstraction (`(<function> <argument>)`).

To see what this means, we will rewrite `charPlusPlus` in lambda terms.

<pre><code> +---- `&lambda;a` introduces an abstraction
 |      where the &lt;body&gt; is `&lambda;b.&lambda;c.[a, b, c]`.
 |
 |        +---- `a` is a name identifying an
 |        |      abstraction point corresponding to `&lambda;a`.
&lambda;a.&lambda;b.&lambda;c.[a, b, c]</code></pre>

When we apply `charPlusPlus` to a `Char` value, we form a function application.

<pre><code>// The &lt;function&gt; is `&lambda;a.&lambda;b.&lambda;c.[a, b, c]`
// and the &lt;argument&gt; is 'c'.

(&lambda;a.&lambda;b.&lambda;c.[a, b, c] 'c')</code></pre>

What happens next?
How does a function perform tasks utilizing the provided argument?
In lambda calculus, when <code>&lambda;x.&lt;body&gt;</code> is applied to `<argument>`, we replace all free occurrences of `x` by `<argument>` inside the `<body>`.
'Free' means the `x` must be in the scope of the corresponding <code>&lambda;x</code>.
For example, <code>(&lambda;x.&lambda;.x.x y)</code> yields <code>&lambda;x.x</code> since the right-most `x` is in the scope of the second <code>&lambda;x</code> and thus hidden from the application.

Hence, the result of applying `charPlusPlus` to `'c'` is a new function.

<pre><code>   (&lambda;a.&lambda;b.&lambda;c.[a, b, c] 'c')
=> &lambda;b.&lambda;c.['c', b, c]</code></pre>

Let us drop the syntax sugar and recreate `charPlusPlus` using anonymous functions.

```Haskell
charPlusPlus :: Char -> Char -> Char -> String
charPlusPlus = \a -> (\b -> (\c -> [a, b, c]))
```

We will once again obtain a new function after applying `charPlusPlus` to `'c'`.

```Haskell
cPlusPlus :: Char -> Char -> String
cPlusPlus = charPlusPlus 'c'
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:30,endLineNumber:12,positionColumn:30,positionLineNumber:12,selectionStartColumn:30,selectionStartLineNumber:12,startColumn:30,startLineNumber:12),source:'module+Main+where%0A%0AcharPlusPlus+::+Char+-%3E+Char+-%3E+Char+-%3E+String%0AcharPlusPlus+%3D+%5Ca+-%3E+(%5Cb+-%3E+(%5Cc+-%3E+%5Ba,+b,+c%5D))%0A%0AcPlusPlus+::+Char+-%3E+Char+-%3E+String%0AcPlusPlus+%3D+charPlusPlus+!'c!'%0A%0Amain::IO()%0Amain+%3D+do%0A++++print+$+charPlusPlus+!'c!'+!'%2B!'+!'%2B!'%0A++++print+$+cPlusPlus+!'%2B!'+!'%2B!'%0A'),l:'5',n:'0',o:'Haskell+source+%231',t:'0')),k:59.793739170473714,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:40.206260829526286,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

While it is not allowed to return a function in C++, we can get around this by returning a function object. We will reimplement our C++ version of `charPlusPlus` using lambda expressions.

```C++
auto charPlusPlus = [](char a) 
{
    return [a](char b)
    {
        return [a, b](char c) -> string
        {
            return {a, b, c};
        };
    };
};

auto cPlusPlus = charPlusPlus('c');
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwAcpK4AMngMmAByPgBGmMQSZqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwc5gDM4cjeWADUJrtuTjPEmKxn2CYaAIJ7B0eYp%2BdUXgx1AmJ3D2eTy86SMx2YbAUySYW2OM3QZysT0BTC8RGOyAQTWU3gUOJBHwAIqcAKxWEmEiCYprHJjLU7IgDsSMexzZx2uBA2DFJFiYJgpVKxxGOMWWgPZp2ZEsl7M53N5TFIooFlOpIuQ9IAtHc4QRiOFgDLZVKWSaTfLiDyTMylaLlaZGYTEcbZTbnbszez3S6mR6WSi0agMfi8biiRjhaHQxAwBxkHHxZ7AYDwgRjiwmOFjhBxUyvWy0GiPm4zm5I9jcTG4wmOMtYztLImG9ZEyWy8c4wK3Awu8mnpKi%2Bmyx3kNHcS2m3XJxZE77nk66/pOCTeH4OFpSKhOKXLNY4etNu89jxSARNHXVgBrEAkrgAOkZZjMkjMjICkgAnFIX0laJxJF4FgJA0DRSHXTdtw4XgFBAMDzw3Jc4FgGBEBATBVFqIMyAoCAmmAPFDC6IQEFQAB3ddTzQFhkjoJgemUIjaBI8iIN4ajaPoBJgB/UgOLoeJIlYbZ2NQGiBOIAB5NEWIoi9gkw5BHmIAjOF4DDagafB114fhBBEMR2CkGRBEUFR1EQ0hdC4fRDGMaxrH0PAYlgyBVlQZIelgjgtXhM5CVMPdLDMSCADd4gNLBXNzUhiG%2BRw2AAFVQTxotWBRDy2PR4XCRiImY0i5O4XgyOIJhkk4HhVn/DhV3A%2BSoOwRTsOOVQAgANi1drJGOYBkGQY4pHvMwc13KxLGVXBCBIU4zF2Lhll4BCtGWa8QEkSR7y4DqAg0drQO/DbdhJEllw4QDSGA%2Bb7w0SQNE/W7GV2fadpstitzU2w4LPC9VmQtCNOQbDyEofDCPy2TKNE8SDAYpjIfk/iuJQAwjC4b8wKRwThM%2BrGpJkwr3sB5TVOghTNIIbTPr04RRHEYyabMtR5N0P87JQByJtoZy0q3TzMm83zKf8wLxosELeFQcLiEizBebiwQ8CSlLaF5jKNiymycoYPLiMJyqSrKiriuqlc1wazgmqwogRTazruoxVHgEGz8tpu0bOZsY4ppt2b5sWn7ENW0gEBuLAEhimqLquswbvargNECZ6SW/KoTvqyyoJg77lqQ1CICQQHgdwsHdYK1iDb4sTOPozIy4Ryy8ZAULkGSZIAH1QvR9vYblgh29Ubqq5h7G2Fx6uJOk4R9cs4mVO89TFK08JqdkAz6ekRmlGZyzdF2WyjA5oKbG5lz4Hc/mBG8gB6eEj7FiWt2l2X5fipXMGS1Lz7WDWjLGbT64z1PKVcqBtTa1XNpnS2zVfaDx6iwBQLdjhd1dr3GYHtj6TXwL7E8Adc7B1DkwcOlBwHRxAM9e8ARPy7Xau1Khu0NDo2ehnSCn1YLwV%2BmtSQARhqMkZCSJ8XASQaACAIlO0gaq7Egawsm%2BDwFmGkZLT6cjSDS3SM4SQQA%3D%3D)

Note that this process can be abstracted so that it works for every function requiring three arguments.

```C++
auto curry(auto f)
{
    return [f](auto a) 
    {
        return [f, a](auto b)
        {
            return [f, a, b](auto c)
            {
                return f(a, b, c);
            };
        };
    };
}
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM6SuADJ4DJgAcj4ARpjE/gDMpAAOqAqETgwe3r56KWmOAiFhkSwxcVxctpj2BQxCBEzEBFk%2BfgF2mA4Z9Y0ERRHRsQm2DU0tOZUKo32hA6VDFQCUtqhexMjsHObxocjeWADUJvFuTlPEmKzH2CYaAILbu/uYRydUXgxdAmLXtw/3XjSRgOzDYCiSTA2Bym6GOVnufyYXiIB2QCEaym8CkxgIgaMaByYpFR6OIByixPxZOQiwOAFprtCCMRQsAjgiAOzwu4HXkHC4ENYMI5conkykmDkAEThf0lMoR9yRKOQa2IAE8IMrUAcqIs5Vy/nz%2BZhBcRhSYAKwWKhWqVa5E6pi0o18yXc43GgVCo7WqjEph2h0oqL6%2B6et2G8MRz3e82%2Bm0B4lRIPa1Fhnkx43u11ZiNx4VULXJyn6%2BIevO8%2BWy6MR6vl3MimUNzkK/53NOq4gszDuUk47FY15S1FqzVUgcDsvcxGO1GTofHEddnt9jFYgcQMAcZDb6dy%2B6hAgHFhMUIHCAZnO11GrY/HNwP0fdvC9tz9jdYrc7vff6y/7d/w4F0TifQDLTcBhAJbTNeTQZFXkfE550/XFAMsACtgw4CaweaVgP0ThLV4PwOC0UhUE4R9LGsaFVnWF5th4UgCE0YDlgAaxAS0uAAOg5MwzEkMwOQADkkABOKQhICWhOEkXgWAkDQNFIUjyMojheAUEBVNYsiCLgWAYEQEBMFUTpHTICgtWIYBsUMaohAQVAAHdSOYtAWCSOgmFqZRHNoZy3PU3gvJ8%2Bg4mAaTSHCuhYnCVhNjC1BvPi4gAHlkWC9y2MCCzkDuOydK0/LOnqfBSN4fhBBEMR2CkGRBEUFR1AM0hdEqAwjBQaxrH0PAoh0yBllQJJahKukYSXUwaMsMwNIAN1iFksGGy9SGID5HDYAAVVBPHW5YFHojY9BhUIArCIKXNy7heFc4gmCSTgeGWOSOGItS8s07ACqsg5VFEgA2OlgckA5gGQZADikXizAvairEsYlcEIEgjjMeIuEWXh9K0RZOJASRJF4rgQdEjRgZUqSSfiS1LUIjgFNIJTsd4jRJA0CTOY5eJqYpypQoozhtN0li2OWIzTPMyyiGsyhGnsq6nNujyUrSgx/MCnLhbiyKUG66KpNU/WEqS0XYtSiLYiy4Q1by2XCuKy2nYq0JLZq4RRHERqvZatQ8t0WTDGMPqUdoQajoo8aMkm6b4ilWbkYsBbeFQZaXzW%2BBli2wQ8D2g7aGjk61jOyYCEqlWbpC16Hqel77veoiSJ%2Bzg/rljGgdB8HUSN2GJLJjnEfDmwDjR%2BXMex3GJYMwnSAQS4sDiDaPpZtmzA54GuA0MxRP5y0pK4MwGe%2B9rNLFvTJdIaWICQJ2rPIRXiur3W66tzW/IyV%2BHfas24kWsgJISQAD6i0uASRAVrTAUwQGqHBh/G2xBEpsEtv/O2b92pOyKvZV2BV3ZVSat7eqEhpD%2ByUIHdquhEhG16nNGwkcho5xjhNTgAB6GEdCU5pwopnVaMDmF5x2pgfah1mGlwYudSul0da/2Yo9Z6ddm6fVbufdu/1J7wIhiwBQgCDjgMHtAqYI96Go3wJPJiM98bsQXkvIYq95KKRAPzXiokJKU2BsDNxlMNAQP5mfDSlsdJXznkTSQol4Ycg5JaASXBLQaFEjEw%2B0gPrxFUYE0q1j54fTMOk9OlssnLEzmkZwkggA%3D%3D)

This is currying.

## Type Signature

The type signatures in Haskell summarize the type characteristics of objects and serve as the targets for the type-checking system.
We already saw them in our `charPlusPlus` examples, where the type signatures appear in the first line of the definitions.

```Haskell
charPlusPlus :: Char -> Char -> Char -> String -- Type signature
charPlusPlus a b c = [a, b, c]
```

```Haskell
charPlusPlus :: Char -> Char -> Char -> String -- Type signature
charPlusPlus = \a -> (\b -> (\c -> [a, b, c]))
```

In the discussion for currying, we noted that the Haskell version of `charPlusPlus` accepts a `Char` value and returns a function requiring two `Char` arguments.
This information is reflected in the type signature as a `Char` value will direct (`->`) us to a function of type signature `Char -> Char -> String`.

In general, the arrow sign `->` is right-associative, meaning `Char -> Char -> Char -> String` is processed as `Char -> (Char -> (Char -> String))` and `Char -> Char -> String` is processed as `Char -> (Char -> String)`.
Therefore, applying `cPlusPlus` to `'+'` yields a new function of type signature `Char -> String`.

```Haskell
cPositivePlus :: Char -> String
cPositivePlus = cPlusPlus '+'
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:30,endLineNumber:16,positionColumn:30,positionLineNumber:16,selectionStartColumn:30,selectionStartLineNumber:16,startColumn:30,startLineNumber:16),source:'module+Main+where%0A%0AcharPlusPlus+::+Char+-%3E+Char+-%3E+Char+-%3E+String%0AcharPlusPlus+%3D+%5Ca+-%3E+(%5Cb+-%3E+(%5Cc+-%3E+%5Ba,+b,+c%5D))%0A%0AcPlusPlus+::+Char+-%3E+Char+-%3E+String%0AcPlusPlus+%3D+charPlusPlus+!'c!'%0A%0AcPositivePlus+::+Char+-%3E+String%0AcPositivePlus+%3D+cPlusPlus+!'%2B!'%0A%0Amain::IO()%0Amain+%3D+do%0A++++print+$+charPlusPlus+!'c!'+!'%2B!'+!'%2B!'%0A++++print+$+cPlusPlus+!'%2B!'+!'%2B!'%0A++++print+$+cPositivePlus+!'%2B!'%0A'),l:'5',n:'0',o:'Haskell+source+%231',t:'0')),k:59.793739170473714,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:40.206260829526286,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

The goal is to summarize a similar characteristic of the metafunctions in this library.
We want to do this for two reasons.

- First, we would like to have theoretical proof of the legitimacy of our composition.
Such proof may be provided by Haskell's type-checking system.
- Second, we would like to create higher-order functions that do structural manipulations only based on the type characteristics of a target metafunction, similar to `std::bind_front` and `curry`.
Many functions of this kind have representations in Haskell.

Let us consider the following metafunction:

```C++
template<typename...>
struct Fun
{
    template<template<typename...> class...>
    struct ProtoRoad
    {
        template<auto...>
        struct ProtoPage
        {
            template<template<auto...> class...>
            struct ProtoRail
            {
                static constexpr bool value {true}; 
            };

            template<template<auto...> class...Sequences>
            using Rail = ProtoRail<Sequences...>;
        };

        template<auto...Variables>
        using Page = ProtoPage<Variables...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};
```

For simplicity, we will use the made-up class-key `alias` to denote a layer. Thus, we represent the structure of `Fun` as the following:

```C++
template<typename...>
struct Fun
{
    template<template<typename...> class...>
    alias Road
    {
        template<auto...>
        alias Page
        {
            template<template<auto...> class...>
            alias Rail
            {
                static constexpr auto value {RESULT};
            }
        };
    };
};
```

Thus, we summarize its type signature as the following:

```Haskell
Fun
 :: typename...
 -> template<typename...> class...
 -> auto...
 -> template<auto...> class...
 -> auto
```

We will translate the symbolic representation above into  Haskell code.

```Haskell
fun
 :: Ellipsis Typename
 -> Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
```

Note that a metafunction is also a template acceptable as a template argument.
Thus, we can reinterpret `Fun` as a value of type `template<typename...>`, or `Template (Ellipsis Typename)` in Haskell.
We will abstract this process into a Haskell function.

```Haskell
reinterpret :: (Ellipsis a -> b) -> Template (Ellipsis a)
reinterpret = undefined
```

Then, we can convert `Fun` into a value of type `Template (Ellipsis Typename)`

```Haskell
reinterpretedFun :: Template (Ellipsis Typename)
reinterpretedFun = reinterpret fun
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:haskell,selection:(endColumn:15,endLineNumber:15,positionColumn:15,positionLineNumber:15,selectionStartColumn:15,selectionStartLineNumber:15,startColumn:15,startLineNumber:15),source:'--+Copyright+2024+Feng+Mofan%0A--+SPDX-License-Identifier:+Apache-2.0%0A%0Amodule+Main+where%0A%0A--+typename%0Adata+Typename%0A%0A--+auto%0Adata+Auto%0A%0A--+*...%0Adata+Ellipsis+a+%3D+Empty+%7C+Dots+a+(Ellipsis+a)%0A%0A--+template%3C*%3E%0Adata+Template+a%0A%0A--+Template+instantiation%0Ainstantiate+::+Template+a+-%3E+a+-%3E+Typename%0Ainstantiate+%3D+undefined%0A%0A--+metafunction+reinterpretation%0Areinterpret+::+(Ellipsis+a+-%3E+b)+-%3E+Template+(Ellipsis+a)%0Areinterpret+%3D+undefined%0A%0A--+fun%0Afun%0A+::+Ellipsis+Typename%0A+-%3E+Ellipsis+(Template+(Ellipsis+Typename))%0A+-%3E+Ellipsis+Auto%0A+-%3E+Ellipsis+(Template+(Ellipsis+Auto))%0A+-%3E+Auto%0Afun+%3D+undefined%0A%0A--+reinterpret+%60fun%60%0AreinterpretedFun+::+Template+(Ellipsis+Typename)%0AreinterpretedFun+%3D+reinterpret+fun%0A%0A--+error+silencer%0Amain+::+IO+()%0Amain+%3D+return+()'),l:'5',n:'0',o:'Haskell+source+%231',t:'0')),k:59.793739170473714,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:ghc961,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:haskell,libs:!(),options:'',overrides:!(),runtimeTools:!(),source:1,stdinPanelShown:'1',tree:0,wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+ghc+9.6.1+(Haskell,+Editor+%231)',t:'0')),k:40.206260829526286,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',m:100,n:'0',o:'',t:'0')),version:4)

Let us examine more examples.

```C++
template<typename Element>
struct Gun
{
    using type = Element;
};

template<template<typename...> class Operation>
struct Pun
{
    template<typename...Elements>
    using Mold = Operation<Elements...>;
};
```

After being provided with all required arguments, `Fun` returns a value via the data member `value`.
Thus, the last arrow in the type signature points to `auto`, or `Auto` in Haskell.

Following the same logic, `Gun` returns a type via the alias member `type`.
Thus, the last arrow in the type signature points to `type`, or `Type` in Haskell. We write out its type signature as follows:

```Haskell
Gun
 :: typename...
 -> typename
```

Or in Haskell notations:

```Haskell
gun
 :: Ellipsis Typename
 -> Typename
```

What is the result of `Pun`?
Since the structure of `Mold` depends on the structure of `Operation`, we do not know what is inside.
Therefore, instead of a class member, we regard the return of the function as the maximum nested submetafunction, `Mold` in the case of `Pun`.
We write out its type signature as follows:

```Haskell
Pun
 :: template<typename...> class...
 -> template<typename...> class
```

Or in Haskell notations:

```Haskell
pun
 :: Ellipsis (Template (Ellipsis Typename))
 -> Template (Ellipsis Typename)
```

We will conclude this section with an example of composition.

First, we compose `Gun` with `Fun`.

```Haskell
funGun
 :: Ellipsis Typename
 -> Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
funGun = fun . (`Dots` Empty) . gun
```

The backticks convert `Dots` into an infix operator, meaning ``Dots a b <=> a `Dots` b``.
Then, we partially apply `` `Dots` `` to `Empty` so that the result from `Gun` will fill in the parameter before `` `Dots` ``. Therefore, :

```Haskell
ellipsisGun :: Ellipsis Typename -> Ellipsis Typename
ellipsisGun =  (`Dots` Empty) . gun
```

Then, we will instantiate `funPun` by a `Typename` `void` and compose `gun` with the result.

```Haskell
voidifiedFunGun
 :: Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
voidifiedFunGun = funGun $ Dots void Empty
```

The dollar sign `$` evaluates the right-side expression first. It is equivalent to a pair of parentheses surrounding the right-side expression.

Finally, we compose `pun` with `funGun`.

```Haskell
funGunPun
 :: Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
funGunPun = voidifiedFunGun . (`Dots` Empty) . pun
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AImCgNaZatUkvrICeAZUboAwqloBXFgwkB2UhcAGTwGTAA5bwAjTGIQAA4ANlIAB1QFQkcGdy8ff1T0zIEQsMiWGLikm0tMeyyhAiZiAhzvXy4A21qHAQamghKI6NiE5IVG5ta8jpsJgdCh8pGkgEobVE9iZHYOAFpdgGp3FIBPYjxgBAIDgCYNG8kDgDFGYAOAWVQqQwBSDQBBfYHITKAAiAA1diFtgwlLsAJJYQR4GgjA7/FJMZAITC7G4AOg0f3%2BxJYGE89A%2BTFCBwA7jjiJhicSgQQTilGKwmQD0ExGgcACrszlsZkAoFMTxEYm8/n/KWoMWAw4AKnx6plfKYB2wVjwKQyCgO2p%2BAGZQTqWCk2Qcfn5XAdQagCEbtRBdbR9YbjSslazMFaDAQmabXCqzdhNfyBQGUkHMMa/YcY4G%2BQnQuNDA4%2BVliRnGsi0wcQCBBbH48aDrsI5Xq6bsILhcxRQD81m8EWzRbPAwsDQwugkx9MI0qD26gIDozQsHiClGY0egxidPBLF5yPi6X3XqDXhXVWa1EVof62XU8GDjvPXvXb6AavZxvrl2Dj2%2BwtBwCWYcx8uAX%2BxJbjqu7ekKHLNty/yng2HpevuV4pnGRbXvBRrgSKmArPe0F1rBoEIfK0oAjBIE3t6EBIRWqG3uiCrYUBeF0cR/x/ra5pvr2mD9pgX4kuKhyPuuC68U8PYrpgM7CSOok9sBVEoXBtEYZBOFCXOInoGJDDsRa6nPgcgHfgJBzAOJAJmf%2B0ElmRaGNhBXKMTWKmORZcmvu%2B3GfkOKTmRifnAUpFEKZeNFgU2XIMSRTEhQmYUIS5bA4b5OkeVxPF8T%2BByWOR%2B4AOJ%2BTlaEFTpNlBQlEVsKR5XoZVUFFbeJW6QcV4/IkGhOi6bUaJa1onCe%2BKmX5WXuFa6QJt1lndXShAILa7WAe1xJ/iVQFlQRtUOS2uE1jViHlopG32ZhUU7Wee1EYq0W7UdlEHaFF30ThpGXctPZNa%2BbGDRA3WdQo03YFabIDUNVlZQAbqgeB8ZD0PyXVxKw%2BgzWeRlQ7wrCBbZpe3UreJ7UHFEJzzRoSPdYjUP4FQskMKtJHrblRp3RecV7YlWHPUxj0sdVt2xVe3OoKdL0KhT0MojTH0cXjOkACSOs6RpI71bJDqNaRKCTKXTbSs0k0jEtae9%2BNEgBxsMMoAUM3ZzPIQ9R3s8LXNHa913nXz92sy7T1OWeruseblupRxBvU0btNyd9v2KwDQP9Qcg3a8Zyo6sQxAkAcGT0Aw2zEKS1KlaW8IAPJXjhLAF81C6bDpEArBway0JwACsvC%2BBwWikKgnAABKmBYViZxsWwTTcpo8KQBCaA3axmCAzcAJz4n4C%2Bmn4poLx0GiSOvfhSPonCSLwLASBoGikO3nfdxwvAKCA59Tx3DekHAsBIJgqi1AqZAUBATTAAoZQhhLBCAQKgWk7cJ5oCtHQHMAggFhFoKA8Bl9eDQJSHQEYlxkAL0SFwUg6DMHEHCFyTgaDUAwPoMQYuUpkEQOnoET%2ByB/jEAAWQxhtQGj4HbrwfgggRBiHYPvPh8glBqAYbofBBgjAgBMOYHK%2Bg8BRDvpANYqBrRZDvjfLu4NYjnCwCouupBiA9gcGwAUqAPCGLWAoYe2w9DjG4QgkBYD6HcF4AQRk7Bz60mIEwFInAeCNxbm3Bh19sBMO/gcVQSRdiJEeNgg4S9Ej4i4FePu8irCkB1PgIgxBbRjy4PXSe09sKkDnpIDQ%2BI7iJBuO1eINwF7NzqTcKoTcOBHwvmE9hd8H6lOCRwG4x9T7n1QV3dhj8tBlN0cQDIThJBAA)

In this library, we compose functions using `Trip` or `ClassicTrip` from various namespaces. Both behave similarly to the dot `.` in Haskell.
The `ClassicTrip` pulls the alias member `type` out of the instantiated function when the next function requests a `typename`.
Meanwhile, the `Trip` directly passes the instantiated function as a `typename` if requested by the next function.

```C++
template<typename...Args>
using FunGun = Mouldivore::ClassicTrip<Gun>
::Road<Fun>
::Commit
::Mold<Args...>;

template<template<typename...> class...Args>
using VoidifiedFunGun = FunGun<void>
::Road<Args...>;

template<template<typename...> class...Args>
using FunGunPun = Roadrivore::Trip<Pun>
::Flow<VoidifiedFunGun>
::Commit
::Road<Args...>;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxBIaABykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BXIF2mA5Zjc0EJZExcQnJCk0tbXmdtpODYcPlo1WJAJS2qF7EyOwcAPT7ANQeKQCexHjACARHZhpmkkcAYozARwCyqFSGJhoAgocjkJlAARAAaAFpQrsGEpIQBJLCCPA0UZHf4pJjIBCYSFmAB0Gj%2B/xJ%2BwAVJTyS8vAwjlTyfsSQRMCwUgYWSYAMxuAhnFKMViYAki7nYEkTYheBw0hgkkz%2BKwAo4qo4stkczDc3ms9lMTk8vkC5hsEUEsVHZAGBQKM1ikmqo6S6W3ZTEVBEABKqCY6AdqoVSv%2Bjsd6r1BrcTC8RDtXPFypDKudMrdHtQyiYwC1CcTgf9idDus12rDxZ5UZjorjluttqr8eDBcdydd7q9TDo%2BabRzzOe7zaajmQloEE0wqhSxCO0VQniOADcxF5MD3FQQpVr/KDuRYe32mwrt1yg12m6X9VrDUWL9qK6hY9ga0wbWahJgAI7Lhi7BT2/cFrwMiMI5PQ7Wgey5UEjlTdtOx5N9P0YH8Hx3U8Ay3VCATQlVzwjO8zQANWaPAmGiehfzjbCjkAsJ3gzLMIKgmD00zS83CIy5SPIlDjy7Q9MNJPtcLY4SS35QVTXrJ8XxFDxBA7cJiAohtHRo4DvV9RjoLbVANL9Hk5KaRYlJ4k8MN4rCAQpKkjgAcVpekqSZAFRMNcSTRXbB6DYQQ/3%2BFs7NpeVFS7NT3iNFduSgrzWUYAgBP4izBMBBloIchlnP%2BVydQ1G83ONIUH2khQjgAeQFYh9SyPyAuUIKsJCoTrwjCKPLNGKfIIZTQqA94vlodAtPKuIqoEbUOriutzUopLEpPKzUq%2BLwBrwecSHYEA3FrPBkAAFUuFJHMpTKPIULFdk%2BLYVrW4hIsa5Lsse9zCqkq1nxK0D8FQGr1xdE5tr2g7gqDQtcpa5qROeyTpsfN6bROZo/IHKUUx0vS%2BPupsAo8FgWEIKje0bbsnoK6GhCuZhaG6/8QzCy6Bq0yNiDE0mV0%2BpxtXJ4BKamsUQBACL7SSg9zJB9Cj3mom1QhksZfyiThVe2szX%2BYBbtiwRqalum9K05j0Z5VX1c63mZrMiX5Qa7dLJSmy9MuG6Nv2vBDoyklTvOtmfXQB31tXSXHrlnLw0h1mirh03YdrEDfQ5yiAQC52UmBrtA7BkSg9al6YeK8Po6ZpHVVqnTnloVAAHcMbFxNsdQXH8Zp/2qNVNOQ5ZhW8/e18KbELX%2B2o3qQO9xnEZ5dnvvgnuqYffnhPp/TxWFgs5oxi2bdBtur3T2Xt/ltqla7g%2BZIJI3MA1rrC5VOnS4rvWS7LyvDbVs%2BTdM4K1%2BS/ibesylZXsuk3YuUzlDRWJ9iDAC1tfWk/8tJLWuutfmW13o7STtqf%2Bfl%2BYGzcM8IK8d/iILrnjeKAJ%2Bb9X0m4f44DI4JQWjZAiqA8D4DROgHBDAYGAKypnYBYcj5TUoRAvydN6GMNRHgTALDoEOSin/XBbg1qMIwSALB/DqGzVob/Vh/86oAKcsyLhu9eQgM7sfFRgjB6aNpNorS9tVoIJAKgnk2jFE30fuxBhTCxESLYbghsBD67EPwUo722oVFv2/gyCJkTMo/2pLtTAEwSocJiZEiJmV5RmC5GEK0XgsAQTcGgb8mAUgXzwXogxWdoY/RRrcfhND/KDh2gAfXenEAgEAJjoH5goIUzSKLYMkQwJxhtwFilIJbf4rC0GyPkQvWe4lFFYKGRQkZcZSGeAXuMsUawdwcA2LQTgABWXgfgOBaFIKgTgbhrDWCdFsHYkUMk8FIAQTQuyNgAGsQAHMkESSQnQuQaAOQ8AAbMCswiRkj7I4JIXgLAEgaFICcs5FyOC8AUCABFLzTm7NIHAWAMBEAgC2AQFI0ZyCUDQGyOgcQIhCk4KoRIwLITAqeMAZAw4pAEjMLwcRhASCML0PwQQIgxDsCkDIQQigVDqGxaQXQXBSDl0qikTgPA9mHOOa885nBSrRlJbcb4RwGVMpZUcNlHKflmCOBAHGKRqVTnMFyLgaxeBYq0BsCASBKV2voGQCgEBvX2pAMAKQZg%2BB0BZEpSg0QtXRDCM0M4qreBxuYMQM4pVojaB6Fip5lLOqlQYLQRNsqsDRC8MASMtAqZJtIFgFghhgDiBLXgW6vR5zxK1eOHo0Y9hPLCCyKFZzaB4GiJVNNHgsBavXHgOF3BeDtuIDOJQoJWQNuHUYV5GwqAGAgQRMR5dhonKeUK4QohxDipPVKtQWr5X6AbSga5lh9AjvRZADYqBilZHRRwSEHSoqmEsNYe4vBUALsuFgV9EANjdF6M4CArhpgdCCAwdAQwygVD0GkDI9RsieHaJhwoOG0MjEqDUOofR5iIb0DBnD/QWjEeWKRiYAwqMKuY/RxY6GVjQbubsCQ6qOBHMRVqlFRrGXMtZeyo4nKrUQFwHyh1jyXXPM3RsXEvpRhQdIJ8yQXICQAE4uT%2BEkBoSQjxgUaEBcC/T%2BhOAwtIHCp1BJgVcGBYkfTiRXPfK4AcwzwLhOypRWijFKnsUeoJZ6oleqyX%2BsDb62lbBODNBYPOfwkImBPmAlwfTBIuBEh5fgIg4HBWyBFee6Ql6lDXtlboMNSqmAqrnQJoTSKQM6uiwaqgRxkupfS5l942XctEmtba%2B1PYMlmGU26nFkW4txHJQGuuPrRg9bS29Iw2WqjhtoJG9FEAY2ypTQmmtR200ZqzQ4Gtea4oFqLVq0t5bK3VrnbW1dRgm1nPwK2xw7bv1nK7cgHtNb%2B21C1cO0dCaJ17DOdO2dTyF1LswCu%2Bt73aKbr4DuhQe7MAHuNDWk9ZWxUVdkFemVZzat3o3QBqwT7weQffZ%2B0cnBf0EH0qCanQHkVgcYR2t9ZHs1ZBcCh1jyHUOcZIwR7DWQRdYaKAwBjGG2O1AFw0SjeGZj89gwwOjCxSgS7Y2r3ISH2O66WIrnj2w%2BPOts4JzVgXODdeICltLGX1sDZy3ljQ1r5NFfG06qbqnSDqawPELTUL7OOZy6Z/wvn/D%2BC5GZyQLKFWte1ai2wIXpvhfgJF4l%2BqFtzeIAlvYyXTUsAUPOYc85BuagmAVhTAqFUE7PUTiV8gqtk50CALkirlVJua3b5F7WSXRiOIa0vTxy%2BV4XDXi8EwRtLbG46rkAewu4q9Yv31BfN%2BjErykFIjTq/6cabXggzSncsu27t6Nsb41ppO3f9Nmbs1XcITdwtxbPuYDLRWsQz2nl1prrQ68BfYC6/adqqDdosjA6CCg6yrg5jpnBQ5TqXBw7zpxCI7I5rpo5r7bqZhY77qHr46lYt4SDE6Sod43rd6U7GCPo2B07wAM44bfr7AdIPqAaWDAbnLc4QaMGa44ZC7uDq5IYhDi6MaS5y4y6EZZAK4rD8EUYsbCHUbK5a466yFMaG74YG4DDqH8abCW5ioD4BZD4cCO4sBl4V5V6z4sjz5yaFYkB%2B7OquqB7B6aYCYR4gBmA5ZchcgHJAp/KWY%2BH%2BBubGFtbp7oqYqB46YHIGYHKJBmDWaSD6bx5GZcA95QpciD5hHOFhYCbcqhFp45HuobALoZDOCSBAA%3D%3D)
