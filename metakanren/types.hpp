/**
   @file metakanren/types.hpp

   @brief This file contains a small amount of functionality to facilitate working
   with types.
   
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
#ifndef TYPES_HPP_INCLUDED_347081871831200829
#define TYPES_HPP_INCLUDED_347081871831200829 1

//
// ... Standard header files
//
#include <cstddef>
#include <typeinfo>


namespace metakanren
{
  namespace types
  {

    /** A wrapper for types.
	this struct template wrappes types, which can be used to move types
	to the  value universe for printing or for other purposes.
     */
    template< typename t >
    struct Type
    {
      using type = t;
    };


    //
    // ... Below, printing is facilitated for various fundamental types.
    //
    
    template< typename stream, typename t >
    stream& operator <<( stream& s, Type< t > ){ return s << typeid( t ).name(); }

    template< typename stream >
    stream& operator <<( stream& s, Type< char > ){ return s << "char"; }

    template< typename stream >
    stream& operator <<( stream& s, Type< unsigned char > ){ return s << "unsigned char"; }

    template< typename stream >
    stream& operator <<( stream& s, Type< short > ){ return s << "short"; }

    template< typename stream >
    stream& operator <<( stream& s, Type< unsigned short > ){ return s << "unsigned short"; }
  
    template< typename stream >
    stream& operator <<( stream& s, Type< int > ){ return s << "int"; }

    template< typename stream >
    stream& operator <<( stream& s, Type< unsigned int > ){ return s << "unsigned int"; }


    template< typename stream >
    stream& operator <<( stream& s, Type< long long > ){ return s << "long long"; }

  
    template< typename stream >
    stream& operator <<( stream& s, Type< unsigned long long > ){ return s << "unsigned long long"; }
  
    template< typename stream >
    stream& operator <<( stream& s, Type< float > ){ return s << "float"; }


    template< typename stream >
    stream& operator <<( stream& s, Type< double > ){ return s << "double"; }


    template< typename stream >
    stream& operator <<( stream& s, Type< size_t > ){ return s << "size_t"; }



    
    /** A wrapper for values.
	The intent of this wrapper in to move values into the type universe.
	The functionality is limited to integral values that can be held as
	template parameters.
    */
    template< typename t, t x >
    struct datum
    {
      using type = t;
      constexpr static t value = x;
    };
  
    template< typename stream, typename t, t x >
    stream& operator <<( stream& s, Type< datum< t, x > > ) { return s << "datum<" << Type< t >() << ',' << x << '>'; }


  };  // end of namespace types

}; // end of namespace metakanren

#endif // ! defined TYPES_HPP_INCLUDED_347081871831200829
