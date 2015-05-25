/**
   @file test/five_test.cpp

   @brief A simple unification test.
   
   @author Samuel B. Johnson <sabjohnso@yahoo.com

   @copyright  2015: Samuel B. Johnson.

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

//
// ... Standard header files
//
#include <type_traits>
#include <iostream>

//
// ... metakanren header files
//

#include <metakanren/metakanren.hpp>

using namespace metakanren;



template< typename ... >
struct g;

template< typename t >
struct g< t >
{
  using type = typename equate< t, datum< size_t, 5 > >::type;
};

using result  = typename apply< typename call_fresh< procedure< g > >::type, empty_state >::type;
using a = typename car< result >::type;
using b = typename cdr< result >::type;

int
main()
{
  std::cout << Type< result >() << std::endl;
  
  static_assert( std::is_same< a, cons< cons< cons< var<0>, datum<size_t,5> >, nil >, datum< size_t, 1 > > >::value, "" );
  static_assert( std::is_same< b, nil >::value, "" );
  
  return 0;
}


