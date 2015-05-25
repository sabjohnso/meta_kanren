/**
   @file metakanren/metakanren.hpp

   @brief User-level functionality.
   
   @author Samuel B. Johnson <sabjohnso@yahoo.com>

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
#ifndef USER_HPP_INCLUDED_565582220337615838
#define USER_HPP_INCLUDED_565582220337615838 1


//
// ... metakanren header files
//
#include <metakanren/core.hpp>



namespace metakanren
{
  namespace user
  {

    using namespace metakanren::core;


    using empty_state = cons< nil, datum< size_t, 0 > >;



  
    template< typename ... >
    struct zzz;

    template< template< typename ... > class f >
    struct zzz< procedure< f > >
    { 
      
      template< typename ... >
      struct g;

      template< typename sc >
      struct g< sc >
      {

	template< typename ... >
	struct h;

	template< typename ... >
	struct h
	{
	  using type = typename f< sc >::type;
	};
	
	using type = procedure< g >;
	
      };
      
      using type = procedure< g >;
    };

    template< typename ... >
    struct conj_plus;

    template< template< typename ... > class g >
    struct conj_plus< procedure< g > >
    {
      using type = typename zzz< procedure< g > >::type;
    };

    template<
      template< typename ... > class g0,
      template< typename ... > class g1,
      template< typename ... > class ... gs >
    struct conj_plus< procedure< g0 >, procedure< g1 >, procedure< gs > ... >
    {
      using type =  typename conj<
	typename zzz< procedure< g0 > >::type,
	typename conj_plus< procedure< g1 >, procedure< gs > ... >::type
	>::type;
    };


    template< typename ... >
    struct disj_plus;

    template< template< typename ... > class g >
    struct disj_plus< procedure< g > >
    {
      using type = typename zzz< procedure< g > >::type;
    };

    template<
      template< typename ... > class g0,
      template< typename ... > class g1,
      template< typename ... > class ... gs
      >
    struct disj_plus< procedure< g0 >, procedure< g1 >, procedure< gs > ... >
    {
      using type = typename disj<
	typename zzz< procedure< g0 > >::type,
	typename disj_plus< procedure< g1 >, procedure< gs > ... >::type
	>::type;
    };


    template< typename ... >
    struct fresh;

    template<
      template< typename ... > class g,
      template< typename ... > class ... gs >
    struct fresh< procedure< g >, procedure< gs > ... >
    {
      using type = typename conj_plus< procedure< g >, procedure< gs > ... >::type;
    };

    template<
      typename x,
      typename y,
      template< typename ... > class g,
      template< typename ... > class ... gs
      >
    struct fresh< cons< x, y >, procedure< g >, procedure< gs > ... >
    {

      template< typename ... >
      struct f
      {
	using type = typename fresh< y, procedure< g >, procedure< gs > ... >::type;
      };
      
      using type = typename call_fresh< procedure< f > >::type;
      
    };


    template< typename ... >
    struct pull;

    template< template< typename ... > class f >
    struct pull< procedure< f > >
    {
      using type = typename pull< typename f<>::type >::type;
    };

    template< typename x >
    struct pull< x >
    {
      using type = x;
    };

    


    template< size_t, typename ... >
    struct take;

    template<  typename ignored >
    struct take< 0, ignored >
    {
      using type = nil;
    };

    template< size_t n, typename lg >
    struct take< n, lg >
    {
      using  f = typename pull< lg >::type;
      using type = typename std::conditional<
	null< f >::value,
	nil,
	cons< typename car< f >::type,
	      typename take< n-1, typename cdr< f >::type >::type
	      >
	>::type;
    };



    template< typename ... >
    struct take_all;

    template< typename lg >
    struct take_all< lg >
    {
      using f = typename pull< lg >::type;
      using type = typename std::conditional<
	null< f >::value,
	nil,
	cons<
	  typename car< f >::type,
	  typename take_all< typename cdr< f >::type >::type
	  >
	>::type;
    };

    
    template< typename ... >
    struct conde;

    template<
      typename x,
      typename y,
      typename ... xs,
      typename ... ys >
    struct conde< cons< x, y >, cons< xs, ys > ... >
    {
      using type = typename disj_plus<
	typename conj_plus< x, y >::type,
	typename conj_plus< xs, ys >::type ...
	>::type;
    };


    template< typename ... >
    struct walk_star;

    template< typename v, typename s  >
    struct walk_star< v, s >
    {
      using u = typename walk< v, s >::type;

      template< typename ... >
      struct aux;

      template< size_t i >
      struct aux< var< i > >
      {
	using type = var< i >;
      };

      template< typename x, typename y >
      struct aux< cons< x, y > >
      {
	using type = cons< typename walk_star< x, s >::type,
			   typename walk_star< y, s >::type >;
      };

      template< typename w >
      struct aux< w >
      {
	using type = w;
      };
    
      using type = typename aux< u >::type;
      
    };


    
  } // end of namespace user
} // end of namespace metakanren




#endif // ! defined USER_HPP_INCLUDED_565582220337615838
