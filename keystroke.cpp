#include <assert.h>

#include "keystroke.hpp"

void KeyStroke::subtract( KeyStroke * const prefix )
{
  for ( deque<char>::iterator i = prefix->user_bytes.begin();
	i != prefix->user_bytes.end();
	i++ ) {
    assert( *i == user_bytes.front() );
    user_bytes.pop_front();
  }
}

string KeyStroke::diff_from( KeyStroke const & existing )
{
  string ret;

  deque<char>::iterator my_it = user_bytes.begin();

  for ( deque<char>::const_iterator i = existing.user_bytes.begin();
	i != existing.user_bytes.end();
	i++ ) {
    assert( my_it != user_bytes.end() );
    if ( *i != *my_it ) {
      fprintf( stderr, "BUG: existing state has %c and new state has %c\n",
	       *i, *my_it );
    }
    assert( *i == *my_it );
    my_it++;
  }

  while ( my_it != user_bytes.end() ) {
    ret += string( &( *my_it ), 1 );
    my_it++;
  }

  return ret;
}

void KeyStroke::apply_string( string diff )
{
  for ( string::iterator i = diff.begin();
	i != diff.end();
	i++ ) {
    user_bytes.push_back( *i );
  }
}