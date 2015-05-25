/**
   @file test/a_and_b.cpp

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
struct f;

template< typename a >
struct f< a >
{
  using type = typename equate< a, datum< size_t, 7 > >::type;
    
};

template< typename ... >
struct g;

template< typename b >
struct g< b >
{
  using type = typename disj<
    typename equate< b, datum< size_t, 5 > >::type,
    typename equate< b, datum< size_t, 6 > >::type >::type;
};

using a_and_b = typename conj<
  typename call_fresh< procedure< f > >::type,
  typename call_fresh< procedure< g > >::type
  >::type;

 using result = typename  apply< a_and_b, empty_state >::type;



  

using sol0 = typename caar< result >::type;
using nxt0 = typename cdar< result >::type;
static_assert( is_list< sol0 >::value, "" );
static_assert( is_assoc< sol0 >::value, "" );
static_assert( std::is_same< sol0,
	       typename list< cons<var<1>, datum<size_t,5>>,
	                      cons<var<0>, datum<size_t,7>> >::type >::value, "");
static_assert( nxt0::value == 2, "" );


using sol1 = typename caadr< result >::type;
using nxt1 = typename cdadr< result >::type;




int
main( int argc, char** argv )
{
  using namespace metakanren;

  std::cout << Type< result >() << std::endl;
  std::cout << Type< typename car< result >::type >() << std::endl;


  std::cout << std::endl << std::endl
	    << "Solution 0" << std::endl
	    << "**********" << std::endl
	    << Type< sol0 >() << std::endl;

  std::cout << std::endl << std::endl
	    << "Solution 1" << std::endl
	    << "**********" << std::endl
	    << Type< sol1 >() << std::endl;
 


  
  return 0;
}
