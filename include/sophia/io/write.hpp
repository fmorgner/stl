#ifndef SOPHIA_IO__WRITE
#define SOPHIA_IO__WRITE

#include "sophia/internal/ordered_evaluator.hpp"

#include <iostream>
#include <type_traits>

namespace sophia::io
  {

  /**
   * @ingroup sophia_io
   * @author Felix Morgner
   * @since 0.1
   *
   * @brief Typesafe output to arbitrary objects of type std::ostream
   */
  template<typename StreamType,
           typename = std::enable_if_t<std::is_base_of<std::ostream, StreamType>::value, void>,
           typename... ValueTypes>
  void write(StreamType & stream, ValueTypes const & ...values)
    {
    ::sophia::internal::ordered_evaluator{(stream << values)...};
    }

  /**
   * @ingroup sophia_io
   * @author Felix Morgner
   * @since 0.1
   *
   * @brief Typesafe output to the standard output device
   */
  template<typename... ValueTypes>
  void write(ValueTypes const & ...values)
    {
    write(std::cout, std::forward<ValueTypes const &>(values)...);
    }

  /**
   * @ingroup sophia_io
   * @author Felix Morgner
   * @since 0.1
   *
   * @brief Typesafe line output to arbitrary objects of type std::ostream
   */
  template<typename StreamType,
           typename = std::enable_if_t<std::is_base_of<std::ostream, StreamType>::value, void>,
           typename... ValueTypes>
  void writeln(StreamType & stream, ValueTypes const & ...values)
    {
    ::sophia::internal::ordered_evaluator{(stream << values)..., stream << '\n'};
    }

  /**
   * @ingroup sophia_io
   * @author Felix Morgner
   * @since 0.1
   *
   * @brief Typesafe line output to the standard output device
   */
  template<typename... ValueTypes>
  void writeln(ValueTypes const & ...values)
    {
    writeln(std::cout, std::forward<ValueTypes const &>(values)...);
    }

  }

#endif
