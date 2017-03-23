Printf
******

While classic C provides the `varargs` based function ``printf(...)``, output is
normally done in C++ using ``std::ostream`` objects like ``std::cout`` and
``std::cerr``. Using the C++ output streams, while syntactically elegant, is
often not as easy as it seems. Getting the structure of the output just right
is a tricky task, and quickly seeing what the output statement does can be even
trickier. Falling back to ``printf(...)``, which is of course also available in
C++, has some issues however. For example, it can be hard to remember which
formatting placeholder to use with which type is cumbersome and error prone.
This issue is owed to the fact, that `varargs` just don't carry along their type
information.

The :cpp:func:`sophie::io::printf(...) <sophia::io::printf>` family of functions
that is part of **sophia** however, provides an easy to use and **type-aware**
alternative to the classic C-style ``printf(...)`` output function.

Thanks to C++ variadic templates, :cpp:func:`sophia::io::printf(...)
<sophia::io::printf>` carries along the information and functionality of the
types of its arguments, making it easy to produce neatly formatted output while
enabling full customization of the format of user-defined types. It makes use
of a minimalistic pythonesque formatting language, that is easy to use.

Formatting mini-language
========================

The formatting mini-language used by :cpp:func:`sophia::io::printf(...)
<sophia::io::printf>` was designed to be close to the formatting language used
by `Pyhon <https://python.org>`_'s ``format(...)`` function. Currently, it only
supports indexed parameter references like ``{0}``, ``{1}``, etc. For example,
a simple format-string using two placeholders might look like this:

.. code-block:: text

  "The second argument was '{1}', while the first one was '{0}'."

Since :cpp:func:`sophia::io::printf(...) <sophia::io::printf>` uses standard
C++ output streams behind the scenes, built-in data types as well as STL types
that can be printed using ``std::ostream`` objects are formatted automagically.
But what about user-defined types or types from the STL that cannot normally be
printed using ``std::ostream`` objects? :cpp:func:`sophia::io::printf(...)
<sophia::io::printf>` is able to print the type and address of any object you
stuff into it. For example, the following code:

.. code-block:: c++
  :linenos:

  #include <sophia/io/printf.hpp>

  struct unprintable {};

  int main() {
    sophia::io::printf("{0}\n", unprintable{});
  }

Will produce output similar to this:

.. code-block:: text

  <11unprintable@0x7ffcc9e3faaf>

If you want to customize how objects of a user-defined type are printed, you
just have to implement
``std::ostream & operator<<(std::ostream &, type const &)`` for your custom type
and :cpp:func:`sophia::io::printf(...) <sophia::io::printf>` will automatically
print your custom objects just how you want it to.

Function Reference
==================

.. doxygenfunction::
  sophia::io::printf(StreamType&, std::string const&, ValueTypes const&...)

.. doxygenfunction::
  sophia::io::printf(std::string const&, ArgumentTypes const&...)
