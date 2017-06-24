#ifndef SOPHIA_IO__PRINTF
#define SOPHIA_IO__PRINTF

#include "sophia/string/format.hpp"

#include <iostream>

namespace sophia::io
  {

  /**
   * @ingroup sophia_io
   *
   * @brief A type-safe implementation of the classic printf with a python-like format syntax
   *
   * This function provides a type-safe version of the classic printf C API. The syntax of the format string is inspired
   * by the Python format syntax. The parameters are "addressable" in the format string. Addressing an invalid argument
   * index causes the original placeholder to be printed.
   *
   * @par Example:
   * @rst
   * .. code-block:: c++
   *    :linenos:
   *
   *    #include <sophia/io/printf.hpp>
   *
   *    int main()
   *      {
   *      sophia::io::printf(std::clog, "{1} is second argument, {0} is the first!", 1337, 42);
   *      }
   * @endrst
   *
   * @param stream The stream to print to. Must be descendent from std::ostream.
   * @param format A python like format-string using {#} as placeholders, where # is the index of the parameter to print.
   * @param values The values to substitute for the placeholders.
   * @author Felix Morgner
   * @since 0.1
   */
  template<typename StreamType,
           typename = std::enable_if_t<std::is_base_of<std::ostream, StreamType>::value, void>,
           typename ...ArgumentTypes >
  void printf(StreamType & stream, std::string const & format, ArgumentTypes && ...values)
    {
    stream << sophia::string::format(format, std::forward<ArgumentTypes>(values)...);
    }

  /**
   * @ingroup sophia_io
   *
   * @brief A type-safe implementation of the classic printf with a python-like format syntax
   *
   * This function provides a type-safe version of the classic printf C API. The syntax of the format string is inspired
   * by the Python format syntax. The parameters are "addressable" in the format string. Addressing an invalid argument
   * index causes the original placeholder to be printed.
   *
   * @par Example:
   * @rst
   * .. code-block:: c++
   *    :linenos:
   *
   *    #include <sophia/io/printf.hpp>
   *
   *    int main()
   *      {
   *      sophia::io::printf("{1} is second argument, {0} is the first!", 1337, 42);
   *      }
   * @endrst
   *
   * @note This version of the function prints to standard output. See #printf for a more generic version.
   *
   * @param format A python like format-string using {#} as placeholders, where # is the index of the parameter to print.
   * @param values The values to substitute for the placeholders.
   * @author Felix Morgner
   * @since 0.1
   */
  template<typename ...ArgumentTypes>
  void printf(std::string const & format, ArgumentTypes && ...values)
    {
    printf(std::cout, format, std::forward<ArgumentTypes>(values)...);
    }

  }

#endif

