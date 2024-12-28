<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Vocabulary

- [**To Index**](../index.md#introduction-vocabulary)
- [*Prologue*](#prologue)
- [*Template-head*](#template-head)
- [*Metafunction && Function*](#metafunction-and-function)
- [*Namespaces*](#namespaces)
- [*Members*](#members)
- [*Layer && Invocation Order*](#layer-and-invocation-order)
- [*Rearrangement*](#rearrangement)
  - [*Cognate*](#rearranged-functions-cognate)
  - [*Kindred*](#rearranged-functions-kindred)
- [*Summary*](#summary)
  - [*Terms*](#summary-terms)
  - [*Prefixes*](#summary-prefixes)
  - [*Symbols*](#summary-symbols)

## Prologue <a id="prologue"></a>

When I choose a technical expression to use in the documentation, I first attempt to keep it close to the relevant C++ terminologies since they are well-documented and familiar to programmers.
However, C++ terms can be confusing. For example, it is unclear what the 'non-type' in the 'non-type template parameter' refers to, as it looks like the complement of all 'type template parameters'.
Moreover, the term 'template template parameter' not only repeats the same word twice like a typo but also erases the differences between the parameter lists within template template parameters.
The detection of the differences, however, is the key part of this library.

As a result, some vocabulary used in the documentation will have meanings unique to this library.
The goal is to maintain the usual flow of written English while providing insights through the selection of words.
Strict definitions for conventional programming terms have little practical use.
They are there for the convenience of authors who try to be as accurate as possible.
Understanding these terms shall not be a burden for the readers or users, as these terms shall be used intuitively and conventionally.
This is what I want to achieve.

## Template-head <a id="template-head"></a>

The term 'template-head' is introduced by the standard.
It is easier to explain the word by an example.

<pre><code>template ---------------------------------------------------+
<                                                           |
    template&lt;typename...&gt; ------> template-head       template-head
    class ----------------------> type-parameter-key        |
    ...                                                     |
    Args -----------------------> identifier                |
> ----------------------------------------------------------+
struct Vehicle;</code></pre>

This library often uses the term without the hyphen.
This is to make my grammar checker happy.

## Metafunction && Function <a id="metafunction-and-function"></a>

In C++, the word 'metafunction' does not have a decisive definition and often acts as a synonym for 'template'.
In this library, the word represents a class template or an alias template, as these are the only kinds of templates acceptable as template arguments in C++20.
We will use the terms `class metafunction` and `alias metafunction` when the differentiation of the two cases is necessary.

The goal is to define the kind of metafunction this library focuses on.
To start with, we will categorize metafunctions by their primary signatures, where a primary signature is defined as follows:

> A primary signature is:
>
> - `typename` for a type;
> - `auto` for a value;
> - the template head for a template.

Namely, primary signatures extend the notion of template heads by two special cases.
Now, we will define the 'conformed signatures' using recursion.
The two cases added earlier will serve as the base cases for the definition.

> A primary signature is conformed if one of the following is true:
>
> - It is `typename` or `auto`.
> - It is a template head whose parameter list only consists of conformed primary signatures.

With all the preparations done, we can finally define the 'conformed metafunctions', which are the focal point of this library.
Since metafunctions are defined by combining two cases, we will specify when each case yields a conformed metafunction separately.
This is necessary since C++ compilers treat class and alias templates differently.

For the convenience of our discussion, we will extend the concept of primary signature to parameter packs.

> A primary signature is:
>
> - `typename` for `typename...`;
> - `auto` for `auto...`;
> - the template head of `Sig` for `Sig...`.

Now:

> - A class metafunction is conformed if its primary signature is conformed.
> - An alias metafunction is conformed if its parameter list consists of one parameter pack whose primary signature is conformed.

The word 'function' is a shorthand for 'conformed metafunction'.
Note that it differs from the ordinary use case of the word, which generally means a named block in C++.
I adopted this abbreviation for several reasons:

- Most metafunctions discussed in the documentation are conformed, which means repeating the quantifier is often redundant and distracting.
- The term 'metafunction' already indicates the function-like behavior of templates. It is more natural to relate the word 'function' to a template in a metaprogramming library rather than a named block in the usual sense.
- Only a few ordinary functions are mentioned in the documentation. When it appears, the term 'ordinary function' is used for differentiation.

> A Submetafunction of a metafunction is one of the following:
>
> - a class member template or
> - an alias member template or
> - a class member template of a submetafunction of the metafunction or
> - an alias template of a submetafunction of the metafunction.

The term 'thoroughly conformed metafunction' is used when every submetafunction of a conformed metafunction is required to be conformed.

## Namespaces <a id="namespaces"></a>

We will define an equivalence relation on functions to characterize their primary signatures.

> Let M be the set of all functions, define &sim; as follows: &forall; (x, y) &isin; M, x &sim; y &iff; x and y have the same signature.

We will focus our attention on several equivalence classes by &sim;.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Primary Signature</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Typelivore</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Varybivore</code></td>
      <td><code>template&lt;auto...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Mouldivore</code></td>
      <td><code>template&lt;template&lt;typename...&gt; class...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Pagelivore</code></td>
      <td><code>template&lt;template&lt;auto...&gt; class...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Roadrivore</code></td>
      <td><code>template&lt;template&lt;template&lt;typename...&gt; class...&gt; class...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Raillivore</code></td>
      <td><code>template&lt;template&lt;template&lt;auto...&gt; class...&gt; class...&gt;</code></td>
    </tr>
  </tbody>
</table>

In addition to these namespaces, a couple more are introduced to contain functions whose parameters are of the form `Vessel<Items...>`.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Primary Signature of <code>Vessel</code></th>
      <th>Primary Signature of <code>Items</code></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Cotanivore</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
      <td><code>typename</code></td>
    </tr>
    <tr>
      <td><code>Sequnivore</code></td>
      <td><code>template&lt;auto...&gt;</code></td>
      <td><code>auto</code></td>
    </tr>
    <tr>
      <td><code>Warehivore</code></td>
      <td><code>template&lt;template&lt;typename...&gt; class...&gt;</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
    </tr>
    <tr>
      <td><code>Stockivore</code></td>
      <td><code>template&lt;template&lt;auto...&gt; class...&gt;</code></td>
      <td><code>template&lt;auto...&gt;</code></td>
    </tr>
  </tbody>
</table>

Finally, general-purpose functions that do not fit any previously mentioned namespaces are kept in `Omennivore`.

<table>
  <thead>
    <tr>
      <th>Namespace</th>
      <th>Content</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Omennivore</code></td>
      <td>General-purpose functions</td>
    </tr>
  </tbody>
</table>

## Members <a id="members"></a>

We will provide several names for the equivalence classes by &sim;. These names will be used to represent a function within the corresponding equivalence class in the documentation.

<table>
  <thead>
    <tr>
      <th>Name</th>
      <th>Primary Signature</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>Mold</code></td>
      <td><code>template&lt;typename...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Page</code></td>
        <td><code>template&lt;auto...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Road</code></td>
        <td><code>template&lt;template&lt;typename...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Rail</code></td>
        <td><code>template&lt;template&lt;auto...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Flow</code></td>
        <td><code>template&lt;template&lt;template&lt;typename...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Sail</code></td>
        <td><code>template&lt;template&lt;template&lt;auto...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Snow</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;typename...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Hail</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;auto...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Cool</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;template&lt;typename...&gt; class...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Calm</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;template&lt;auto...&gt; class...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Grit</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;template&lt;template&lt;typename...&gt; class...&gt; class...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Will</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;template&lt;template&lt;auto...&gt; class...&gt; class...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Glow</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;template&lt;template&lt;template&lt;typename...&gt; class...&gt; class...&gt; class...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
      <tr>
        <td><code>Dawn</code></td>
        <td><code>template&lt;template&lt;template&lt;template&lt;template&lt;template&lt;template&lt;auto...&gt; class...&gt; class...&gt; class...&gt; class...&gt;&nbsp;class...&gt;&nbsp;class...&gt;</code></td>
      </tr>
  </tbody>
</table>

The interface members of this library's functions are always named after their corresponding equivalence classes.

## Layer && Invocation Order <a id="layer-and-invocation-order"></a>

An illustration might help in understanding the term 'layer'.

<pre><code>template<...> ---------------------------------------------+
Metafunction                                               |
{                                                      0th Layer
    template<...> -----------------------------------+     |
    NestedMetafunction                               |     |
    {                                            1st Layer |
        template<...> -------------------------+     |     |
        NestedMetafunction                     |     |     |
        {                                  2nd Layer |     |
                  ...                          |     |     |
            template<...> ---------------+     |     |     |
            NestedMetafunction      Last Layer |     |     |
            {}; -------------------------+     |     |     |
                  ...                          |     |     |
        }; ------------------------------------+     |     |
    }; ----------------------------------------------+     |
}; --------------------------------------------------------+</code></pre>

Essentially, each layer is a submetafunction, except the *0*th one.
A layer's number suggests its position in the outmost metafunction.
To invoke the (*n* + 1)th layer, the *n*th layer must be instantiated first.
Therefore, the *n*th layer is defined recursively, with the *0*th layer serving as the base case, which is directly invocable.

This is the explanation given to the `*n*th layer` when I first started working on the documentation.
Later, however, I realize it does not cover all the scenarios where I use this word.

In the description for `Flip` functions, I wrote:

> `Namespace::Flip` accepts an operation and flips its *0*th layer and *1*st layer.

How do we flip metafunctions?
The previous explanation won't make sense in this scenario.
To solve this, we need to abstract the notion further.
I introduce the term 'layer' to capture the sequential characteristic of submetafunctions.
But what has been sequenced?
The following illustration might help.

<pre><code><b>Metafunction</b>

template&lt;...Args<sub>0</sub>&gt; ------------------ Declare Args<sub>0</sub>...
Scope<sub>0</sub> { ---------------------------- Args<sub>0</sub>... are injected to the <i>0</i>th scope
    template&lt;...Args<sub>1</sub>&gt; -------------- Declare Args<sub>1</sub>...
    Scope<sub>1</sub> { ------------------------ Args<sub>1</sub>... are injected to the <i>1</i>st scope
        template&lt;...Args<sub>2</sub>&gt; ---------- Declare Args<sub>2</sub>...
        Scope<sub>2</sub> { -------------------- Args<sub>2</sub>... are injected to the <i>2</i>nd scope
                  ...
            template&lt;...Args<sub>Last</sub>&gt; ---- Declare Args<sub>Last</sub>...
            Scope<sub>Last</sub> { -------------- Args<sub>Last</sub>... are injected to the last scope
            };
        };
    };
};</code></pre>

After applying `Flip` to the metafunction, the illustration becomes the following.

<pre><code><b>Flip&lt;Metafunction&gt;::RESULT</b>

template&lt;...Args<sub>1</sub>&gt; ------------------ Declare Args<sub>1</sub>...
Scope<sub>0</sub> { ---------------------------- Args<sub>1</sub>... are injected to the <i>0</i>th scope
    template&lt;...Args<sub>0</sub>&gt; -------------- Declare Args<sub>0</sub>...
    Scope<sub>1</sub> { ------------------------ Args<sub>0</sub>... are injected to the <i>1</i>st scope
        template&lt;...Args<sub>2</sub>&gt; ---------- Declare Args<sub>2</sub>...
        Scope<sub>2</sub> { -------------------- Args<sub>2</sub>... are injected to the <i>2</i>nd scope
                  ...
            template&lt;...Args<sub>Last</sub>&gt; ---- Declare Args<sub>Last</sub>...
            Scope<sub>Last</sub> { -------------- Args<sub>Last</sub>... are injected to the last scope
            };
        };
    };
};</code></pre>

The order of scopes is defined naively.
It is an invariant for rearranged metafunctions.
What was flipped is the declaration order of the parameters.
Take `Typelivore::Plume`, `Typelivore::SensiblePlume`, and one struture of `Mouldivore::BiCognatePlume` as examples:

<pre><code><b>Typelivore::Plume</b>

template&lt;typename...Elements&gt;
Scope<sub>0</sub> {
    template&lt;template&lt;typename...&gt; class...Cosmetics&gt;
    Scope<sub>1</sub> {
        template&lt;template&lt;typename...&gt; class Operation>&gt;
        Scope<sub>2</sub> {
        };
    };
};</code></pre>

<pre><code><b>Typelivore::SensiblePlume</b>

template&lt;typename...Elements&gt;
Scope<sub>0</sub> {
    template&lt;template&lt;typename...&gt; class Operation>&gt;
    Scope<sub>1</sub> {
        template&lt;template&lt;typename...&gt; class...Cosmetics&gt;
        Scope<sub>2</sub> {
        };
    };
};</code></pre>

<pre><code><b>Mouldivore::BiCognatePlume</b>

template&lt;template&lt;typename...&gt; class Operation>&gt;
Scope<sub>0</sub> {
    template&lt;template&lt;typename...&gt; class...Cosmetics&gt;
    Scope<sub>1</sub> {
        template&lt;typename...Elements&gt;
        Scope<sub>2</sub> {
        };
    };
};</code></pre>

Each function contains three scopes.
The order of the scopes is invariant since it is defined by induction and only relies on the total number of scopes.
What separates these functions is the arrangement of `Elements...`, `Cosmetics...`, and `Operation`.

We will define the 'invocation order' first.

> The invocation order of a thoroughly conformed metafunction is a map from the function's canonically defined scopes to a set of parameter lists.

Finally, we will define the '*n*th layer'.

> The *n*th layer is the projection from the *n*th scope to the parameter list it maps to according to the invocation order.

Now, we can understand flipping the *0*th layer and the *1*st layer as an exchange of the projections' destinations.

## Rearrangement <a id="rearrangement"></a>

Based on the discussions above, each function in this library consists of three components:

- Parameter lists.
- Invocation order.
- Effect.

A function's effect is the action it will perform over its parameter lists.
Generally speaking, a function's effect is independent of its invocation order since different orders do not change the final parameter lists eventually received by the algorithm.
We will characterize the similarity of functions that only differ in their invocation orders by the term 'rearrangement'.

> A function `F` is a rearrangement of another function `G` if `F` and `G` have the same parameter lists and perform the same effect. We say `F` and `G` are rearranged functions.

We will use several prefixes in the function's name to distinguish rearranged functions.

### Cognate <a id="rearranged-functions-cognate"></a>

This prefix is used when a function's *0*th layer accepts an operation, which will later be instantiated by the resulting list from the function's effect.
For example, `Mouldivore::BiCognatePlume` is a rearrangement of `Typelivore::Plume`. The function first takes in an operation.
After being provided with `Cosmetics...` and `Elements...`, the function transforms `Elements...` by `Cosmetics...` and instantiates the operation by the result.
(Meanwhile, `Bi` indicates the function handles two scenarios).

For simplicity, I didn't use this prefix when the function's name strongly suggests the operation's existence, such as `Mouldivore::Agent`, `Mouldivore::BindFront`, `Mouldivore::BindBack`, and `Mouldivore::Bind`.
We categorize such functions as 'higher-order modifications' and view them in a way so that they always return a modified operation by altering the parameter lists or the invocation order.

For example, `Mouldivore::Agent` first accepts an operation.
When provided with a packed vessel, the function extracts the items to invoke the operation.
Meanwhile, `Omennivore::Send` first accepts a packed vessel and performs the same effect after being provided with an operation.
Therefore, `Agent` is `CognateSend`.
However, the name `Agent` is shorter and more descriptive.

```C++
template<template<typename...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    { using type = Operation<Elements...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

```C++
template<typename>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail 
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

### Kindred <a id="rearranged-functions-kindred"></a>

This prefix is used when a function's last layer accepts operations or predicates that participate in the algorithm performed by the function. Let us consider the structures of `Mouldivore::Find` and `Typelivore::KindredFind`.

```C++
template<template<typename...> class...Predicates>
struct Find
{
    template<typename...Elements>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };
};
```

```C++
template<typename...Elements>
struct KindredFind
{
    template<template<typename...> class...Predicates>
    alias Road
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };
};
```

In `Mouldivore::Find`, the predicates are accepted first.
When provided with a list of elements, the function returns the index of the first element that satisfies all the predicates, or `-1` if the element is not found.

The rules for the prefix `Cognate` do not apply here since the predicates must be invoked in order to perform the algorithm, meaning the effects of the predicates matter.
In terms of `Cognate`, the first accepted operation acts as a box to present the result of the function's effect, meaning the operation's effect doesn't matter to `Cognate` functions.

Theoretically, it is possible to have prefixed and non-prefixed functions in the same namespace.
For example, the `KindredFind` in the namespace `Mouldivore` will have the following structure.

```C++
template<template<typename...> class...Items>
struct KindredFind
{
    template<template<template<typename...> class...> class...Predicates>
    alias Road
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };
};
```

`Mouldivore::KindredFind` will return the index of the first item that satisfies all the predicates, or `-1` if the item is not found.

Therefore, prefixes are necessary to prevent potential name collisions.

## Summary <a id="summary"></a>

### Terms <a id="summary-terms"></a>

<dl>
  <dt>Alias metafunction</dt>
  <dd>
    An alias metafunction is an alias template.
  </dd>
  
  <dt>Class metafunction</dt>
  <dd>
    A class metafunction is a class template.
  </dd>

  <dt>Conformed alias metafunction</dt>
  <dd>
    An alias metafunction is conformed if its parameter list consists of one parameter pack whose primary signature is conformed.
  </dd>

  <dt>Conformed class metafunction</dt>
  <dd>
    A class metafunction is conformed if its primary signature is conformed.
  </dd>

  <dt>Conformed metafunction</dt>
  <dd>A conformed metafunction is a conformed class metafunction or a conformed alias metafunction.</dd>

  <dt>Conformed primary signature</dt>
  <dd>
    A primary signature is conformed if one of the following is true:
    <ul>
      <li>It is <code>typename</code> or <code>auto</code>.</li>
      <li>It is a template head whose parameter list only consists of the same conformed primary signatures.</li>
    </ul>
  </dd>

  <dt>Container</dt>
  <dd>A container is a vessel that holds types.</dd>

  <dt>Element</dt>
  <dd>Elements denote the arguments held by a container.</dd>

  <dt>Finally-returned function</dt>
  <dd>The finally-returned function of a thoroughly conformed metafunction is the submetafunction corresponding to the last layer.</dd>

  <dt>Function</dt>
  <dd>A function is a conformed metafunction.</dd>

  <dt>Item</dt>
  <dd>
    Items denote the arguments held by a vessel.
  </dd>

  <dt>Invocation order</dt>
  <dd>
    The invocation order of a thoroughly conformed metafunction is a map from the function's canonically defined scopes to a set of parameter lists.
  </dd>

  <dt>Layer</dt>
  <dd>
    The <i>n</i>th layer is the projection from the <i>n</i>th scope to the parameter list it maps to according to the invocation order.
  </dd>

  <dt>Metafunction</dt>
  <dd>A metafunction is a class template or an alias template.</dd>

  <dt>Operation</dt>
  <dd>An operation is a conformed metafunction. The term is used when the focus is on the functionality of the metafunction.</dd>

  <dt>Packed container</dt>
  <dd>A packed container is an instantiation of a container.</dd>

  <dt>Packed sequence</dt>
  <dd>A packed sequence is an instantiation of a sequence.</dd>

  <dt>Packed stockroom</dt>
  <dd>A packed stockroom is an instantiation of a stockroom.</dd>

  <dt>Packed warehouse</dt>
  <dd>A packed warehouse is an instantiation of a warehouse.</dd>

  <dt>Packed vessel</dt>
  <dd>A packed vessel is an instantiation of a vessel.</dd>

  <dt>Primary signature</dt>
  <dd>
    A primary signature is:
    <ul>
      <li><code>typename</code> for a type;</li>
      <li><code>auto</code> for a value;</li>
      <li>the template head for a template.</li>
      <li><code>typename</code> for <code>typename...</code>;</li>
      <li><code>auto</code> for <code>auto...</code>;</li>
      <li>the template head of <code>Sig</code> for <code>Sig...</code>.</li>
    </ul>
  </dd>

  <dt>Primary signature category</dt>
  <dd>
    Let M be the set of all primary signatures, define &sim; as follows: &forall; (x, y) &isin; M, x &sim; y &iff; x and y have the same primary signature. Then a category is an equivalence class in M under &sim;.
  </dd>
  
  <dt>Rank</dt>
  <dd>
    <ul>
      <li>The rank of <code>typename</code> is <code>0</code>;</li>
      <li>The rank of <code>auto</code> is <code>0</code>;</li>
      <li>Otherwise, the rank of a conformed primary signature, say <code>CPS</code>, is <code>1 + (the rank of parameter-primary-signature)</code> where <code>parameter-primary-signature</code> is the primary signature of <code>CPS</code>'s parameter list.</li>
    </ul>
  </dd>

  <dt>Rearrangement</dt>
  <dd>
    A function <code>F</code> is a rearrangement of another function <code>G</code> if <code>F</code> and <code>G</code> have the same parameter lists and perform the same effect. We say <code>F</code> and <code>G</code> are rearranged functions.
  </dd>

  <dt>Sequence</dt>
  <dd>A sequence is a vessel that holds values.</dd>

  <dt>Stockroom</dt>
  <dd>A stockroom is a vessel that holds functions with the primary signature <code>template&lt;auto...&gt;</code>.</dd>

  <dt>Submetafunction</dt>
  <dd>A submetafunction of a metafunction is one of the following:
    <ul>
      <li>a class member template or</li>
      <li>an alias member template or</li>
      <li>a class member template of a submetafunction of the metafunction or</li>
      <li>an alias template of a submetafunction of the metafunction.</li>
    </ul>
  </dd>

  <dt>Thoroughly conformed metafunction</dt>
  <dd>A metafunction is thoroughly conformed if all of its submetafunctions are conformed.</dd>

  <dt>Type result</dt>
  <dd>The alias member <code>type</code> of an instantiated function.</dd>

  <dt>Value result</dt>
  <dd>The static constexpr data member <code>value</code> of an instantiated function.</dd>

  <dt>Variable</dt>
  <dd>Variables denote the arguments held by a sequence.</dd>

  <dt>Vessel</dt>
  <dd>
    A vessel is a conformed metafunction that is used for holding its arguments from an instantiation.
  </dd>

  <dt>Warehouse</dt>
  <dd>A warehouse is a vessel that holds functions with the primary signature <code>template&lt;typename...&gt;</code>.</dd>
</dl>

### Prefixes <a id="summary-prefixes"></a>

<dl>
  <dt>Bi</dt>
  <dd>It indicates the function handles types and values.</dd>

  <dt>Burdensome</dt>
  <dd>It indicates the function handles types, value, <code>Mold</code>s, <code>Page</code>s, <code>Road</code>s, <code>Rail</code>s, <code>Flow</code>s, <code>Sail</code>s, <code>Snow</code>s, <code>Hail</code>s.</dd>

  <dt>Classic</dt>
  <dd>It indicates the function will use the alias member <code>type</code> of the targets when a type is requested.</dd>

  <dt>Cognate</dt>
  <dd>It indicates the function's <i>0</i>th layer accepts an operation, which will later be instantiated by the resulting list from the function's effect.</dd>

  <dt>Cosmopolitan</dt>
  <dd>It indicates the function handles types, value, <code>Mold</code>s, <code>Page</code>s, <code>Road</code>s, <code>Rail</code>s, <code>Flow</code>s, <code>Sail</code>s, <code>Snow</code>s, <code>Hail</code>s, <code>Cool</code>s, <code>Calm</code>s.</dd>

  <dt>Easy</dt>
  <dd>It indicates the function handles types, value, <code>Mold</code>s, and <code>Page</code>s.</dd>

  <dt>Kindred</dt>
  <dd>It indicates the function's last layer accepts operations or predicates that participate in the algorithm performed by the function.</dd>

  <dt>Simple</dt>
  <dd>It indicates the function handles types, value, <code>Mold</code>s, <code>Page</code>s, <code>Road</code>s, and <code>Rail</code>s.</dd>

  <dt>Toilsome</dt>
  <dd>It indicates the function handles types, value, <code>Mold</code>s, <code>Page</code>s, <code>Road</code>s, <code>Rail</code>s, <code>Flow</code>s, and <code>Sail</code>s.</dd>

  <dt>Typical</dt>
  <dd>It indicates the function will return a type by the alias member <code>type</code>.</dd>
</dl>

### Symbols <a id="summary-symbols"></a>

<dl>
  <dt><code>(phrase)&lt;Arg&gt;</code></dt>
  <dd>It turns a phrase into a symbolic prefix function.</dd>
  <dd>
    For example, <code>(make set)&lt;Items...&gt;</code> returns a new list <code>S</code> such that <code>S</code>:
    <ul>
      <li>contains every item in the <code>Items...</code>;</li>
      <li>doesn't contain repetitive items;</li>
      <li>preserves the relative order as in <code>Items...</code>.</li>
    </ul>
  </dd>
  <dd>Angle brackets may be omitted if the indication is evident.</dd>

  <dt><code>(nothing)</code></dt>
  <dd>It represents nothingness.</dd>
  <dd>For example, <code>Operation<(nothing)> <=> Operation&lt;&gt;</code>.</dd>

  <dt><code>(unpack)</code></dt>
  <dd>It extracts items from a packed vessel.</dd>
  <dd>For example, <code>using PackedVessel = Vessel&lt;Items...&gt;</code>,  then <code>Operation<(unpack)PackedVessel> <=> Operation&lt;Items...&gt;</code>.</dd>

  <dt><code>***</code></dt>
  <dd>It represents an unspecific component in an expression.</dd>
  <dd>For example, <code>template&lt;***&gt;</code> represents a random template head.</dd>

  <dt><code>`phrase`</code></dt>
  <dd>It turns a phrase into a symbolic infix function.</dd>
  <dd>For example, <code>A `overlaps` B</code> returns true if <code>A</code> overlaps <code>B</code> and returns false if otherwise.</dd>

  <dt><code>Arg</code></dt>
  <dd>Argument</dd>

  <dt><code>Args</code></dt>
  <dd>Arguments</dd>

  <dt><code>Con</code></dt>
  <dd>Container</dd>

  <dt><code>Cons</code></dt>
  <dd>Containers</dd>

  <dt><code>E</code></dt>
  <dd>Element</dd>

  <dt><code>Es</code></dt>
  <dd>Elements</dd>

  <dt><code>I/J/K</code></dt>
  <dd>Index or indices</dd>

  <dt><code>Init</code></dt>
  <dd>Initiator</dd>

  <dt><code>Inits</code></dt>
  <dd>Initiators</dd>

  <dt><code>Oper</code></dt>
  <dd>Operation</dd>

  <dt><code>Opers</code></dt>
  <dd>Operations</dd>

  <dt><code>Seq</code></dt>
  <dd>Sequence</dd>

  <dt><code>Seqs</code></dt>
  <dd>Sequences</dd>

  <dt><code>Stoc</code></dt>
  <dd>Stockroom</dd>

  <dt><code>Stocs</code></dt>
  <dd>Stockrooms</dd>

  <dt><code>Transf</code></dt>
  <dd>Transformation</dd>

  <dt><code>Transfs</code></dt>
  <dd>Transformations</dd>

  <dt><code>V</code></dt>
  <dd>Variable</dd>

  <dt><code>Vs</code></dt>
  <dd>Variables</dd>

  <dt><code>Ware</code></dt>
  <dd>Warehouse</dd>

  <dt><code>Wares</code></dt>
  <dd>Warehouses</dd>
